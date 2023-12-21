import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import * as dotenv from 'dotenv';
import { DynamoDBClient, PutItemCommand, GetItemCommand } from '@aws-sdk/client-dynamodb';

dotenv.config();

const USER_TABLE = process.env.USER_TABLE;
const SALT_ROUNDS = Number(process.env.SALT_ROUNDS);
const SECRET = process.env.SECRET;

const dynamoDBClient = new DynamoDBClient({});

// Helper Function
const createToken = async ({ id, role }) => jwt.sign({ id, role }, SECRET, { expiresIn: '1d' });

const findUser = async (id) => {
  const command = new GetItemCommand({
    TableName: USER_TABLE,
    Key: {
      id: {
        S: id,
      },
    },
  });
  return await dynamoDBClient.send(command);
};

// Resolver
const registerUserResolver = async (_p, { input }) => {
  const { id, name = 'UserName', password } = input;

  const isUserExist = !!(await findUser(id)).Item;
  if (isUserExist) throw Error('User already Exist');

  const hashedPassword = await bcrypt.hash(password, SALT_ROUNDS);
  const command = new PutItemCommand({
    TableName: USER_TABLE,
    Item: {
      id: {
        S: id,
      },
      name: {
        S: name,
      },
      password: {
        S: hashedPassword,
      },
      role: {
        S: 'COMPANY',
      },
    },
  });
  const response = await dynamoDBClient.send(command);
  return { id, name, role: 'COMPANY' };
};

const loginUserResolver = async (_p, { input }) => {
  const { id, password } = input;
  const user = await findUser(id);

  if (!user.Item) throw Error('User Not Found!');

  const hashedPassword = user.Item.password.S;
  const isPasswordValid = await bcrypt.compare(password, hashedPassword);
  if (!isPasswordValid) throw Error('Wrong Password!');

  const token = await createToken({ id, role: user.Item.role.S });
  return { token };
};

const meResolver = async (_p, _a, { me }) => {
  if (!me) throw Error('Please Login!');
  const meId = me.id;
  const command = new GetItemCommand({
    TableName: USER_TABLE,
    Key: {
      id: {
        S: meId,
      },
    },
  });
  const response = await dynamoDBClient.send(command);
  if (!response.Item) throw Error('User Not Found!');
  const meData = {
    id: response.Item.id.S,
    name: response.Item.name.S,
  };
  return meData;
};

export const Query = {
  me: meResolver,
};

export const Mutation = {
  register: registerUserResolver,
  login: loginUserResolver,
};
