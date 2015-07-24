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
    $scope.numberOptions = [5, 10, 15, 20, 25];
    $scope.matches = {};
    $scope.inputform = {
      x: "511084.873897",
      y: "106120.919667",
      lat: "38.456",
      lng: "-84.123",
      numberOfMatches: 10
    };

    $scope.findProjections = function() {
      var getParams = $scope.inputform;
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
