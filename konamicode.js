/* $Id$ */

/**
 * Konami Code jQuery Plugin
 * Author: Rob Loach
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *                    Version 2, December 2004 
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net> 
 *
 * Everyone is permitted to copy and distribute verbatim or modified 
 * copies of this license document, and changing it is allowed as long 
 * as the name is changed. 
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO. 
 */
(function($) {
  var konamiListeners = [];
  var progress = [];

  $.extend({
    konami: function(callback, sequence) {
      sequence = typeof(sequence) != 'undefined' ? sequence : [38, 38, 40, 40, 37, 39, 37, 39, 66, 65];
      konamiListeners.push({'callback': callback, 'sequence': sequence});
    }
  });

  $(document).bind("keyup", function(event) {
    progress.push(event.keyCode);
    $.each(konamiListeners, function(index, listener) {
      // Only compare if it's a possible full match.
      if (progress.length >= listener.sequence.length) {
        // Create a target sequence that is the same length as the progress.
        var target = progress.slice(progress.length - listener.sequence.length);
        // Check if the result is the same.
        var equals = true;
        for (var i = 0; i < target.length; i++) {
          if (target[i] != listener.sequence[i]) {
            equals = false;
            break;
          }
        }
        if (equals) {
          // Reset the progress and invoke the listener.
          progress = [];
          listener.callback();
          return false;
        }
      }
    });
    // Keep the progress length sane.
    if (progress.length > 40) {
      progress = progress.slice(25);
    }
  });
})(jQuery);

/**
 * Register the Konami Code action behavior.
 */
Drupal.behaviors.konamicode = function(context) {
  // Multiple actions can take place. It defaults to just Image Attack.
  $.each(Drupal.settings.konamicode || {imageattack:true}, function(action, code) {
    var sequence = (code == true) ? [38, 38, 40, 40, 37, 39, 37, 39, 66, 65] : code;
    // Register the Konami Code event.
    $('body:not(.konamicode' + action + ')').addClass('konamicode' + action).each(function() {
      $.konami(function() {
        // Activate the event.
        Drupal['konamicode_' + action]();
      }, sequence);
    });
  });
};

/**
 * The Image Attack Konami Code action.
 */
Drupal.konamicode_imageattack = function() {
  // Subtract Druplicon width and height to ensure that he is only spawned
  // inside the window area and does not cause it to scroll.
  var width = $(window).width() - 175;
  var height = $(window).height() - 200;
  Drupal.konamicode_imageattackimages = Drupal.settings.konamicodeImages || ['http://drupalcode.org/viewvc/drupal/contributions/docs/marketing/logo/druplicon.small.png?view=co'];
  // Select a random image.
  var max = 500;
  var count = 0;
  konamiCodeSpawnImage(width, height, max, count);
};

/**
 * Spawn an image randomly on the screen.
 */
function konamiCodeSpawnImage(width, height, max, count) {
  // Generate random location.
  var x = Math.floor(Math.random() * width);
  var y = Math.floor(Math.random() * height);
  var image = Drupal.konamicode_imageattackimages[Math.floor(Math.random() * Drupal.konamicode_imageattackimages.length)];

  // Append Druplicon image tag to HTML body.
  $('body').append('<img src="' + image + '" style="position: absolute; z-index: 1000; left: ' + x + 'px; top: ' + y + 'px;"/>');
  count++;
  
  // Queue another Druplicon.
  if (count < max) {
    setTimeout('konamiCodeSpawnImage(' + width + ', ' + height + ', ' + max + ', ' + count + ')', 10);
  }
}

/**
 * The Redirect Konami Code action.
 */
Drupal.konamicode_redirect = function() {
  window.location = Drupal.settings.konamicodeDestination || 'http://bacolicio.us/' + window.location;
};

/**
 * The Alert Konami Code action.
 */
Drupal.konamicode_alert = function() {
  alert(Drupal.settings.konamicodeAlert || Drupal.t('Konami Code is geek!'));
};

/**
 * The Flip Text Konami Code action.
 */
Drupal.konamicode_fliptext = function() {
  $('body').fliptext();
};
