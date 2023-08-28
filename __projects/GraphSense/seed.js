var db = require("./models");

var user_bob = {
  email: "bob@bob.com",
  password: "123456",
  userName: "Bob"
};

var graphs = [  
  {
    title: "Graph One",
    content: "In software systems, it is often the early bird that makes the worm."
  },
  {
    title: "Graph Two",
    content: "Every program has (at least) two purposes: the one for which it was written, and another for which it wasn't."
  },
  {
    title: "Graph Three",
    content: "One man's constant is another man's variable."
  }
];

db.User.remove({}, function(){
  db.Graph.remove({}, function(){
    db.User.create(user_bob, function(err, user){
      if (err || !user) { return console.log(err); }
      var user_bob_graphs = graphs.map(function(p){p.user = user._id; return p;});
      db.Graph.create(user_bob_graphs, function(err, graphs){
          if (err) { return console.log(err); }
          console.log("Created", posts.length, "graphs");
          process.exit();
        }
      );
    });
  });
});
