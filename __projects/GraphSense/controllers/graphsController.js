var auth = require('../middleware/auth');
var db = require('../models'),
    User = db.User,
    Graph = db.Graph;

function index(req, res) {
  Graph
    .find({})
    .populate('user')
    .exec(function(err, graphs){
      if (err || !graphs || !graphs.length) {
        return res.status(404).send({message: 'Graphs not found.'});
      }
      res.send(graphs);
    });
}

function create(req, res){
  var new_graph = new Graph(req.body);
  new_graph.user = req.user_id;
  new_graph.save(function(err, new_graph){
    res.send(new_graph);
  });
}

function show(req, res){
  Graph
    .findById(req.params.id)
    .populate('user')
    .exec(function(err, found_graph){
      if (err || !found_graph) {
        return res.status(404).send({message: 'Graph not found.'});
      }

      res.send(found_graph);
    });
}

function update(req, res){
  var query = {
    _id: req.params.id
  };

  if (req.user_id) {
    query.user = req.user_id;
  }

  Graph
    .findOneAndUpdate(query, req.body)
    .exec(function(err, graph){
      if (err || !graph) {
        console.log(graph);
        return res.status(404).send({messsage: 'Failed to update graph.'});
      }
      res.status(204).send();
    });
}

function destroy(req, res){
  var query = {
    _id: req.params.id
  };

  if (req.user_id) {
    query.user = req.user_id;
  }

  Graph
    .findOneAndRemove(query)
    .exec(function(err, graph){
      if (err || !graph) {
        return res.status(404).send({messsage: 'Failed to delete graph.'});
      }
      res.status(204).send();
    });
}

module.exports = {
  index: index,
  create: create,
  show: show,
  update: update,
  destroy: destroy
};
