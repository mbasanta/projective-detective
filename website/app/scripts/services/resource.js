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
  .factory('FindProj', function ($resource, AppConfig) {
    return $resource(AppConfig.apiUrl + '/find_proj');
  });

})(angular);
