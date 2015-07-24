'use strict';

(function(angular) {

/**
 * @ngdoc function
 * @name projectiveDetectiveApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the projectiveDetectiveApp
 */
angular.module('projectiveDetectiveApp')
  .controller('MainCtrl', function ($scope, FindProj) {
    $scope.matches = {};

    $scope.findProjections = function() {
      var getParams = $scope.inputform || {};
      console.log(getParams);
      var proj = FindProj.get(
        getParams,
        function() {
          console.log(proj);
          $scope.matches = proj.matches;
        },
        function() {
          console.log('fail');
        }
      );
    };
  });

})(angular);
