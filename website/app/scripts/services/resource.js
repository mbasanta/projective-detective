'use strict';

(function(angular) {

/**
 * @ngdoc function
 * @name projectiveDetectiveApp.factory:FindProj
 * @description
 * # FindProj
 * Service for the REST resources of the projectiveDetectiveApp
 */
angular.module('projectiveDetectiveApp')
  .factory('FindProj', function ($resource) {
    return $resource('http://localhost:5000/find_proj');
  });

})(angular);
