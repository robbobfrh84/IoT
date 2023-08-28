angular
  .module('GraphSense', [
    'ngRoute',
    'satellizer',
    'pubnub.angular.service'
    ])
  .controller('MainController', MainController)
  .controller('GraphsIndexController', GraphsIndexController)
  .controller('GraphsNewController', GraphsNewController)
  .controller('GraphsShowController', GraphsShowController)
  .controller('LoginController', LoginController)
  .controller('SignupController', SignupController)
  .controller('LogoutController', LogoutController)
  .controller('ProfileController', ProfileController)
  .controller('ChatCtrl', function($scope, Pubnub) {
   $scope.channel = 'test';
   // Generating a random uuid between 1 and 100 using an utility function from the lodash library.
   $scope.uuid = _.random(100);
   Pubnub.init({
     publish_key: 'pub-c-a3ff103c-13da-40f7-9134-45670c77ae43',
     subscribe_key: 'sub-c-8740379a-1fcd-11e6-8b91-02ee2ddab7fe',
     ssl: true,
     uuid: $scope.uuid
  });
  })
  .service('UserService', UserService)
  .config(configRoutes);
