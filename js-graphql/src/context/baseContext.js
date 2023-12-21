import jwt from 'jsonwebtoken';

const SECRET = process.env.SECRET;

const baseContext = async ({ request }) => {
  const token = request.headers.get('x-token');
  if (token) {
    try {
      const me = await jwt.verify(token, SECRET);
      return { me };
    } catch (error) {
      throw new Error('Your session expired. Please sign in again.');
    }
  }
};

export default baseContext;
