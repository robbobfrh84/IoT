UsersIndexController.$inject = ["$http"]; // minification protection
function UsersIndexController ($http) {
  var vm = this;
  vm.users = [];

  query(); // fetch all the users (index)
  ////

  function query() {
    $http
      .get('/api/user')
      .then(function onSuccess(response) {
        vm.users = response.data;
      });
  }
function isLoggedIn(){
  if(usersIndexCtrl.user._id === main.currentUser.user_id);
}
}
