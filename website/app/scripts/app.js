'use strict';

(function(angular) {

/**
 * @ngdoc overview
 * @name projectiveDetectiveApp
 * @description
 * # projectiveDetectiveApp
 *
 * Main module of the application.
 */
angular
  .module('projectiveDetectiveApp', [
    'ngMessages',
    'ngResource',
    'ngRoute'
  ])
  .config(function ($routeProvider) {
    $routeProvider
      .when('/', {
        templateUrl: 'views/main.html',
        controller: 'MainCtrl',
        controllerAs: 'main'
      })
      .when('/about', {
        templateUrl: 'views/about.html',
        controller: 'AboutCtrl',
        controllerAs: 'about'
      })
      .otherwise({
        redirectTo: '/'
      });
  });

angular.module('projectiveDetectiveApp')
  .constant('AppConfig', {
    apiUrl: 'http://' + location.hostname + ':5000'
  });

})(angular);
