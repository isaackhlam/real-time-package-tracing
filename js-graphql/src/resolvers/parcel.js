import * as dotenv from 'dotenv';
import { DynamoDBClient, GetItemCommand } from '@aws-sdk/client-dynamodb';

dotenv.config();

const PACKAGE_TABLE = process.env.PACKAGE_TABLE;

const dynamoDBClient = new DynamoDBClient({});

const findPackageResolver = async (_p, { input }) => {
  const { id } = input;
  const command = new GetItemCommand({
    TableName: PACKAGE_TABLE,
    Key: {
      packageId: {
        S: id,
      },
    },
  });
  const response = await dynamoDBClient.send(command);
  if(!response.Item) throw Error('Package Not Found!');

  const geoLocation = {
    longitude: response.Item.lastUpdateLongitude.S,
    latitude: response.Item.lastUpdateLatitude.S,
  };
  return { location: geoLocation, lastUpdateTime: response.Item.lastUpdateTime.S };
};

export const Query = {
  findPackage: findPackageResolver,
};
