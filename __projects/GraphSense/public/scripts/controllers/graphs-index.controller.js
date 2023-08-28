GraphsIndexController.$inject = ["$http"]; // minification protection
function GraphsIndexController ($http) {
  var vm = this;
  vm.graphs = [];

  query(); // fetch all the graphs (index)
  ////

  function query() {
    $http
      .get('/api/graphs')
      .then(function onSuccess(response) {
        vm.graphs = response.data;
      });
  }
function isLoggedIn(){
  if(graphsIndexCtrl.user._id === main.currentUser.user_id);
}
}
