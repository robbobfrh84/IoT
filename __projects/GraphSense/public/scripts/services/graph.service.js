angular.module('mean.graphs').factory('Graphs', ['$resource',
  function($resource) {
    return $resource('graphs/:graphId', {
      graphId: '@_id'
    }, {
      update: {
        method: 'PUT'
      }
    });
  }
]);
