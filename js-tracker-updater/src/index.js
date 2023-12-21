exports.handler = async ({ body }) => {
  console.log(body);
  return {statusCode: 200, body: {message: 'OK!'}};
}
