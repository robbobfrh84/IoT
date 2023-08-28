var mongoose = require('mongoose');
mongoose.connect( process.env.MONGODB_URI ||
                  process.env.MONGOHQ_URL ||
                'mongodb://localhost/graphSense');

module.exports = {
  User: require("./user"),
  Graph: require("./graph")
};
