/**
 * This is the main server script that provides the API endpoints
 *
 * Uses sqlite.js to connect to db
 */
require('dotenv').config()

const db = require("./sqlite.js");

const fastify = require("fastify")({
  // Set this to true for detailed logging:
  logger: false
});

const routes = { endpoints: [] };

const errorMessage =
  "Whoops! Error connecting to the database, please try again!";

fastify.register(require("@fastify/formbody"));

// OnRoute hook to list endpoints
fastify.addHook("onRoute", routeOptions => {
  routes.endpoints.push(routeOptions.method + " " + routeOptions.path);
});

// Just send some info at the home route
fastify.get("/", (request, reply) => {
  const data = {
    title: "Endpoints da estacao metereologica",
    routes: routes.endpoints
  };
  reply.status(200).send(data);
});

// Return the leituras leituras from the database helper script - no auth
fastify.get("/leituras", async (request, reply) => {
  let data = {};
  data.leituras = await db.getLeituras();
  console.log(data.leituras);
  if (!data.leituras) data.error = errorMessage;
  const status = data.error ? 400 : 200;
  reply.status(status).send(data);
});

// Add new leitura (auth)
fastify.post("/leitura", async (request, reply) => {
  let data = {};
  const auth = authorized(request.headers.admin_key);
  if (!auth || !request.body || !request.body.leitura) data.success = false;
  else if (auth) data.success = await db.addMessage(request.body.leitura);
  const status = data.success ? 201 : auth ? 400 : 401;
  reply.status(status).send(data);
});

// Delete a leitura (auth)
fastify.delete("/leitura", async (request, reply) => {
  let data = {};
  const auth = authorized(request.headers.admin_key);
  if (!auth || !request.query || !request.query.id) data.success = false;
  else data.success = await db.deleteMessage(request.query.id);
  const status = data.success ? 201 : auth ? 400 : 401;
  reply.status(status).send(data);
});

// Helper function to authenticate the user key
const authorized = key => {
  if (
    !key ||
    key < 1 ||
    !process.env.ADMIN_KEY ||
    key !== process.env.ADMIN_KEY
  )
    return false;
  else return true;
};

// Run the server and report out to the logs
fastify.listen({ port: process.env.PORT || '3000', host: '0.0.0.0' }, function (err, address) {
  if (err) {
    console.error(err);
    process.exit(1);
  }
  console.log(`Your app is listening on ${address}`);
});
