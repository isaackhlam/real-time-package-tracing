import { DynamoDBClient, PutItemCommand, QueryCommand } from '@aws-sdk/client-dynamodb';

const TRACKER_LOCATION_TABLE = process.env.TRACKER_LOCATION_TABLE;
const PACKAGE_TABLE = process.env.PACKAGE_TABLE;

const dynamoDBClient = new DynamoDBClient({});

const updatePackage = async ({
  trackerId = "Unregister",
  trackerType = "Truck",
  rfid,
}) => {
  const queryCommand = new QueryCommand({
    TableName: TRACKER_LOCATION_TABLE,
    KeyConditionExpression: "id = :id",
    ExpressionAttributeValues: {
      ":id": { S: trackerId },
    },
    ScanIndexForward: false,
    Limit: 1
  });

  let response = await dynamoDBClient.send(queryCommand);

  const {
    time,
    latitude,
    longitude,
  } = response.Items[0];

  const putCommand = new PutItemCommand({
    TableName: PACKAGE_TABLE,
    Item: {
      packageId: {
        S: rfid
      },
      locationId: {
        S: trackerId
      },
      locationType: {
        S: trackerType
      },
      lastUpdateTime: {
        S: time.S
      },
      lastUpdateLatitude: {
        S: latitude.S
      },
      lastUpdateLongitude: {
        S: longitude.S
      },
    },
  });
  response = await dynamoDBClient.send(putCommand);

  return {
    statusCode: 200,
    body: {response}
  };
}

const updateTrackerLocation = async ({
  trackerId = "Unregister",
  time,
  latitude,
  longitude,
}) => {
  console.log(trackerId, time, latitude, longitude)
  const command = new PutItemCommand({
    TableName: TRACKER_LOCATION_TABLE,
    Item: {
      id: {
        S: trackerId,
      },
      time: {
        S: time,
      },
      latitude: {
        S: String(latitude),
      },
      longitude: {
        S: String(longitude),
      },
    },
  });
  const response = await dynamoDBClient.send(command);
  return {
    statusCode: 200,
    body: {response}
  };
}

export const handler = async ({body}) => {
  const request = JSON.parse(body);
  console.log("Request Body: ", request);
  let resp;
  if (request.topic === "gps")
    resp = updateTrackerLocation(JSON.parse(request.message));
  else
    resp = updatePackage(JSON.parse(request.message));
  console.log("Response: ", resp);
  return resp;
}
