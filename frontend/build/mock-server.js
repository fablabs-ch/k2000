const jsonServer = require('json-server')
const server = jsonServer.create()
const router = jsonServer.router('static/cocktail.json')
const middlewares = jsonServer.defaults()
const SSE = require('express-sse')
const status = {
  carrierDistMm: 0,
  payloadWeightGr: 0
}
const sse = new SSE()

server.get('/api/sse/status', sse.init)
setInterval(() => {
  sse.send(status)
  status.carrierDistMm = Math.round(Math.random() * 500)
  status.payloadWeightGr += Math.round(Math.random() * 10)
  if (status.payloadWeightGr > 500) {
    status.payloadWeightGr = 0
  }
}, 1000)

// Set default middlewares (logger, static, cors and no-cache)
server.use(middlewares)
server.use(jsonServer.bodyParser)

// Add custom routes before JSON Server router
server.post('/api/command/order', (req, res) => {
  console.log(req.body)
  if (Array.isArray(req.body) &&
       req.body.every((i) => i.hasOwnProperty('ingredientId') && i.hasOwnProperty('ml'))) {
    // 409 if busy
    Math.random() > 0.5 ? res.send('ok') : res.sendStatus(409)
  } else {
    res.sendStatus(500)
  }
})

server.post('/api/command/stop', (req, res) => {
  res.send('ok')
})

server.get('/api/debug/move/:mm', (req, res) => {
  console.log(req.params)
  res.send(true)
})

server.get('/api/debug/servo/:servoId/:aperture', (req, res) => {
  console.log(req.params)
  res.send(true)
})

server.get('/api/debug/fill/:mm/:servoId/:aperture', (req, res) => {
  console.log(req.params)
  res.send(true)
})

server.get('/api/debug/tare', (req, res) => {
  res.send('not implemented')
})

server.get('/api/debug/test/:message', (req, res) => {
  res.send('ok')
})

// Use default router
server.use('/api', router)
server.listen(3000, () => {
  console.log('JSON Server is running')
})
