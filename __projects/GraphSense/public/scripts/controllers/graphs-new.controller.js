GraphsNewController.$inject = ["$location", "$http"]; // minification protection
function GraphsNewController ($location, $http) {
  var vm = this;
  vm.create = create;
  vm.graph = {}; // form data

function create(){
  $http
    .post('/api/graphs', vm.graph)
    .then(onCreateSuccess, onCreateError);

function onCreateSuccess(response){
  $location.path('/graphs/' + response.data._id);
}
function onCreateError(response){
  console.error("Failed to create graph", response);
  }
}

}
