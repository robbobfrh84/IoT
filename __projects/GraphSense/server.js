// require express and other modules
var express = require('express'),
    app = express(),
    bodyParser = require('body-parser'),
    logger = require('morgan'),
    auth = require('./middleware/auth'),
    controllers = require("./controllers");

// require and load dotenv
require('dotenv').config({silent: true});

// configure bodyParser (for receiving form data)
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// serve static files from public folder
app.use(express.static(__dirname + '/public'));

// log api requests
app.use(logger('dev')); //middleware of logging in terminal each get/put etc

/*
 * Auth Routes
 */

var usersCtrl = controllers.users;
app.post('/auth/signup', usersCtrl.signup);
app.post('/auth/login', usersCtrl.login);
app.get('/api/me', auth.ensureAuthenticated, usersCtrl.showCurrentUser); //checks wristband to pass to controller action, you can have as many as you want in the middle of the parenthasis
app.put('/api/me', auth.ensureAuthenticated, usersCtrl.updateCurrentUser);

/*
 * API Routes
 */

var graphsCtrl = controllers.graphs;
app.get('/api/graphs', graphsCtrl.index);
app.post('/api/graphs', auth.ensureAuthenticated, graphsCtrl.create);
app.get('/api/graphs/:id', graphsCtrl.show);
app.put('/api/graphs/:id', auth.ensureAuthenticated, graphsCtrl.update); //matching this update, making sure the user id is same as request, need ensureAuthenticated
app.delete('/api/graphs/:id', auth.ensureAuthenticated, graphsCtrl.destroy);


/*
 * Catch All Route
 */
app.get(['/', '/signup', '/login', '/logout', '/profile', '/graphs*'], function (req, res) {
  res.sendFile(__dirname + '/views/index.html');
});


/*
 * Listen on localhost:3000
 */
var port = process.env.PORT || 3000;
app.listen(port, function() {
  console.log('server started on port ', port);
});
