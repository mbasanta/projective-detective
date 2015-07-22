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
  .controller('MainCtrl', function ($scope) {
    $scope.matches = {
      "ATF (Paris)": 98210.48587019218,
      "NAD83 / Kentucky Single Zone (ftUS)": 0.0,
      "NAD83(2011) / Kentucky Single Zone (ftUS)": 0.0,
      "NAD83(HARN) / Kentucky Single Zone (ftUS)": 0.0,
      "NAD83(NSRS2007) / Kentucky Single Zone (ftUS)": 0.0,
      "NTF (Paris)": 98210.48587019218,
      "Panama-Colon 1911 / Panama Polyconic": 83469.70741358143,
      "Tananarive (Paris)": 98210.48587019218,
      "Voirol 1875 (Paris)": 98210.48587019218,
      "Voirol 1879 (Paris)": 98210.48587019218
    };

    $scope.findProjections = function() {
      console.log($scope.inputform);
    };
  });

})(angular);
