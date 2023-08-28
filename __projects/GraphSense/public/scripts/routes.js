configRoutes.$inject = ["$routeProvider", "$locationProvider"]; // minification protection
function configRoutes($routeProvider, $locationProvider) {

  //this allows us to use routes without hash params!
  $locationProvider.html5Mode({
    enabled: true,
    requireBase: false
  });

  $routeProvider
    .when('/', {
      templateUrl: 'templates/user/index.html',
      controller: 'GraphsIndexController',
      controllerAs: 'home'
    })
    .when('/signup', {
      templateUrl: 'templates/user/signup.html',
      controller: 'SignupController',
      controllerAs: 'sc',
      resolve: {
        skipIfLoggedIn: skipIfLoggedIn
      }
    })
    .when('/login', {
      templateUrl: 'templates/auth/login.html',
      controller: 'LoginController',
      controllerAs: 'lc',
      resolve: {
        skipIfLoggedIn: skipIfLoggedIn
      }
    })
    .when('/logout', {
      template: null,
      controller: 'LogoutController',
      resolve: {
        loginRequired: loginRequired
      }
    })
    .when('/profile', {
      templateUrl: 'templates/user/profile.html',
      controller: 'ProfileController',
      controllerAs: 'profileCtrl',
      resolve: {
        loginRequired: loginRequired
      }
    })
    .when('/graphs', {
      templateUrl: 'templates/graphs/index.html',
      controller: 'GraphsIndexController',
      controllerAs: 'home'
    })
    .when('/graphs/new', {
      templateUrl: 'templates/graphs/new.html',
      controller: 'GraphsNewController',
      controllerAs: 'graphsNewCtrl',
      resolve: {
        loginRequired: loginRequired
      }
    })
    .when('/graphs/:id', {
      templateUrl: 'templates/graphs/show.html',
      controller: 'GraphsShowController',
      controllerAs: 'graphsShowCtrl'
    })
    .when('/graphs/index/:title', {
            templateUrl: 'views/graphs/index.html'
    })
    .otherwise({redirectTo: '/'});

    function skipIfLoggedIn($auth) {
      if ($auth.isAuthenticated());
    }

    function loginRequired($location, $auth) {
      if (!$auth.isAuthenticated()) {
        $location.path('/login');
      }
    }

}
