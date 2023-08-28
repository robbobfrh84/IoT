GraphsShowController.$inject = ["$location", "$http", "$routeParams"]; // minification protection
function GraphsShowController ($location, $http, $routeParams) {
  var vm = this;
  vm.destroy = destroy;
  vm.graph = {};

  var id = $routeParams.id;
  get(); // fetch one graph (show)

  function get() {
    $http
      .get('/api/graphs/' + id)
      .then(onGetSuccess, onGetError);

    function onGetSuccess(response){
      vm.graph = response.data;
    }

    function onGetError(response){
      console.error("Failed to get graph", response);
      $location.path("/");
    }
  }

  function destroy() {
    $http
      .delete('/api/graphs/' + id)
      .then(onDeleteSuccess, onDeleteError);

    function onDeleteSuccess(response){
      $location.path("/");
    }

    function onDeleteError(response){
      console.error("Failed to delete graph", response);
    }
  }

  $scope.findOne = function() {
      Graphs.get({
        graphId: $stateParams.graphId
      }, function(graph) {
        $scope.graph = graph;
      });
    };


}
