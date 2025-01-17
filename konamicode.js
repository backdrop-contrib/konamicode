(function ($) {
  var konamiListeners = [];
  var progress = [];

  $.extend({
    konami: function (callback, sequence) {
      sequence = typeof sequence !== 'undefined' ? sequence : [38, 38, 40, 40, 37, 39, 37, 39, 66, 65];
      console.log('Registered Konami Code listener for sequence:', sequence);
      konamiListeners.push({ 'callback': callback, 'sequence': sequence });
    }
  });

  $(document).bind("keyup", function (event) {
    //console.log('Key pressed:', event.keyCode);
    progress.push(event.keyCode);
    $.each(konamiListeners, function (index, listener) {
      //console.log('Checking sequence for listener:', listener.sequence);
      // Only compare if it's a possible full match.
      if (progress.length >= listener.sequence.length) {
        // Create a target sequence that is the same length as the progress.
        var target = progress.slice(progress.length - listener.sequence.length);
        console.log('Progress:', progress, 'Target:', target);
        // Check if the result is the same.
        var equals = true;
        for (var i = 0; i < target.length; i++) {
          if (target[i] != listener.sequence[i]) {
            equals = false;
            break;
          }
        }
        if (equals) {
          console.log('Konami Code sequence matched for listener:', listener.sequence);
          // Reset the progress and invoke the listener.
          progress = [];
          listener.callback();
          return false; // Exit the loop after a match.
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
Backdrop.behaviors.konamicode = {
  attach: function (context, settings) {
    console.log('Konami Code settings loaded:', settings.konamicode);
    // Multiple actions can take place. Defaults to just Image Attack.
    jQuery.each(settings.konamicode || { imageSpawn: true }, function (action, code) {
      var sequence;
      if (typeof code === 'object' && code.keycode) {
        sequence = code.keycode; // Extract the keycode sequence.
      } else if (code === true) {
        sequence = [38, 38, 40, 40, 37, 39, 37, 39, 66, 65]; // Default sequence.
      } else {
        console.error('Invalid code format for action:', action, code);
        return;
      }

      console.log('Listening for action:', action, 'with sequence:', sequence);
      // Register the Konami Code event.
      jQuery('body').once('konamicode' + action, function () {
        console.log('Konami Code event registered for action:', action);
        jQuery.konami(function () {
          console.log('Konami Code triggered for action:', action);
          // Activate the event.
          if (Backdrop['konamicode_' + action]) {
            Backdrop['konamicode_' + action]();
          } else {
            console.error('No handler found for action:', action);
          }
        }, sequence);
      });
    });
  }
};

/**
 * The Image Attack Konami Code action.
 */
Backdrop.konamicode_imageSpawn = function() {
  const settings = Backdrop.settings.konamicode?.imageSpawn;

  console.log('Image Spawn settings:', settings);

  if (!settings) {
    console.error('Image Attack settings are missing.');
    return;
  }

  // Subtract image dimensions to ensure images spawn within the window area.
  const width = jQuery(document).width() - 175;
  const height = jQuery(document).height() - 200;

  // Parse the images setting into an array.
  const images = settings.images ? settings.images.split('\n') : ['https://backdropcms.org/files/inline-images/Drop.png'];

  // Maximum number of images to spawn.
  const max = settings.max || 500;

  let count = 0;

  // Recursive function to spawn images.
  function spawnImage() {
    if (count >= max) return;

    // Generate random location.
    const x = Math.floor(Math.random() * width);
    const y = Math.floor(Math.random() * height);
    const image = images[Math.floor(Math.random() * images.length)];

    // Append image to the body.
    jQuery('body').append(`<img src="${image}" style="position: absolute; z-index: 1000; left: ${x}px; top: ${y}px;"/>`);
    count++;

    // Schedule the next image spawn.
    setTimeout(spawnImage, 10);
  }

  // Start spawning images.
  spawnImage();
};


/**
 * Spawn an image randomly on the screen.
 */
function konamiCodeSpawnImage(width, height, max, count) {
  // Generate random location.
  var x = Math.floor(Math.random() * width);
  var y = Math.floor(Math.random() * height);
  var image = Backdrop.konamicode_imageSpawnimages[Math.floor(Math.random() * Backdrop.konamicode_imageSpawnimages.length)];

  // Append Druplicon image tag to HTML body.
  jQuery('body').append('<img src="' + image + '" style="position: absolute; z-index: 1000; left: ' + x + 'px; top: ' + y + 'px;"/>');
  count++;

  // Queue another Druplicon.
  if (count < max) {
    setTimeout('konamiCodeSpawnImage(' + width + ', ' + height + ', ' + max + ', ' + count + ')', 10);
  }
}

/**
 * The Redirect Konami Code action.
 */
Backdrop.konamicode_redirect = function() {
  window.location = Backdrop.settings.konamicodeDestination || 'https://youtu.be/dQw4w9WgXcQ';
};

/**
 * The Alert Konami Code action.
 */
Backdrop.konamicode_alert = function() {
  alert(Backdrop.settings.konamicodeAlert || Backdrop.t('Konami Code Is Geek!'));
};

/**
 * The Flip Text Konami Code action.
 */
Backdrop.konamicode_fliptext = function() {
  if (typeof jQuery.fn.fliptext === 'function') {
    jQuery('body').fliptext();
  } else {
    console.error('fliptext plugin is not loaded.');
  }
};

/**
 * The Cornify Konami Code action.
 */
Backdrop.konamicode_cornify = function() {
  jQuery.getScript('https://www.cornify.com/js/cornify.js', function(data, textStatus) {
    cornify_add();
  });
};

/**
 * The Geocities-izer Konami Code action.
 */
Backdrop.konamicode_geocitiesizer = function() {
  var theme = Backdrop.settings.konamicodeGeo || 0;
  if (theme !== 0) {
    theme = '&theme=' + theme;
  }
  else {
    theme = '';
  }
  window.location = 'http://wonder-tonic.com/geocitiesizer/content.php?url=' + window.location + theme;
};

/**
 * The Asteroids Konami Code action.
 */
Backdrop.konamicode_asteroids = function() {
  // Or: https://cdn.jsdelivr.net/gh/erkie/erkie.github.com/asteroids.js.
  //jQuery.getScript('https://hi.kickassapp.com/kickass.js');
  jQuery.getScript('https://cdn.jsdelivr.net/gh/erkie/erkie.github.com/asteroids.js');
};

/**
 * The Replace Images Konami Code action.
 */
Backdrop.konamicode_replaceImages = function () {
  const settings = Backdrop.settings.konamicode?.replaceImages;

  console.log('Replace Images settings:', settings);

  if (!settings || !settings.integrations) {
    console.error('Replace Images settings are missing or not configured properly.');
    return;
  }

  // Map integrations to URLs.
  const integrationUrls = {
    baby: 'https://hendrasusanto.com/placebabies/',
    bacon: 'https://baconmockup.com/',
    bear: 'https://placebear.com/',
    beer: 'https://placebeer.com/',
    nicolas_cage: 'https://www.placecage.com/',
    geese: 'https://placegeese.com/',
    kitten: 'https://placecats.com/',
    lorem_picsum: 'https://picsum.photos/',
    lorem_pixel: 'http://lorempixel.com/',
  };

  // Create a list of enabled integrations.
  const enabled = Object.entries(settings.integrations)
    .filter(([key, value]) => value && integrationUrls[key]) // Ensure the value is truthy and the URL exists.
    .map(([key]) => integrationUrls[key]);

  // Default to placecats.com if no integrations are enabled.
  if (enabled.length === 0) {
    enabled.push('https://placecats.com/');
  }

  console.log('Enabled integrations:', enabled);

  // Replace every image element on the page.
  jQuery('img').each(function () {
    const width = jQuery(this).width() || 100;
    const height = jQuery(this).height() || 100;
    const source = enabled[Math.floor(Math.random() * enabled.length)];
    jQuery(this).attr('src', source + width + '/' + height);
  });
};

/**
 * The Raptorize Konami Code action.
 */
Backdrop.konamicode_raptorize = function() {
  // Load the Raptorize plugin via jQuery.
  jQuery.getScript(Backdrop.settings.konamicodeR + '/raptorize/jquery.raptorize.1.0.js', function() {
    // Display the Raptor's wrath.
    jQuery('body').raptorize({
      'enterOn': 'timer',
      'delayTime': 50
    });
  });
};

/**
 * The Katamari Hack Konami Code action.
 */
Backdrop.konamicode_katamari = function() {
  //jQuery.getScript('http://kathack.com/js/kh.js');
  jQuery.getScript('https://cdn.jsdelivr.net/gh/seancron/kathack/kh.js');
};

/**
 * The Snowfall Konami Code action.
 */
Backdrop.konamicode_snowfall = function() {
  // Check if snowfall settings exist and include a path.
  if (!Backdrop.settings.snowfall) {
    console.error('Snowfall settings are missing in Backdrop.settings.');
    return;
  }

  var path = Backdrop.settings.snowfall + '/snowfall/snowfall.jquery.js';

  // Load the Snowfall jQuery plugin.
  jQuery.getScript(path, function() {
    console.log('Snowfall script loaded successfully from:', path);

    // Invoke the plugin on the document object with default or custom settings.
    jQuery(document).snowfall({
      flakeCount: 35,  // Default or configurable
      flakeColor: '#ffffff',
      minSize: 2,
      maxSize: 5,
      minSpeed: 1,
      maxSpeed: 5,
      round: true,
      shadow: true,
    });
  }).fail(function() {
    console.error('Failed to load the Snowfall plugin from path:', path);
  });
};


/**
 * The GG Konami Code action.
 */
Backdrop.konamicode_gg = function () {
  // Ensure the path for GG settings is loaded correctly.
  const ggBasePath = Backdrop.settings.gg || '';
  if (!ggBasePath) {
    console.error('Konami Code GG path is missing.');
    return;
  }

  // Append the `/gg/` subdirectory to the path.
  const ggPath = ggBasePath.endsWith('/') ? `${ggBasePath}gg/` : `${ggBasePath}/gg/`;

  // Only add the Konami Code GG once.
  if (jQuery('#konamicode-gg').length === 0) {
    const extensions = ['ogg', 'mp3', 'wav'];
    let markup = '<audio id="konamicode-gg" preload="auto">';
    extensions.forEach((ext) => {
      markup += `<source src="${ggPath}gg.${ext}" />`;
    });
    markup += '</audio>';
    jQuery('body').append(markup);
  }

  // Play the GG sound.
  const audioElement = jQuery('#konamicode-gg')[0];
  if (audioElement) {
    audioElement.play();
  } else {
    console.error('Failed to play Konami Code GG sound. Audio element not found.');
  }
};

/**
 * The Browser Ponies Code action.
 */
Backdrop.konamicode_browserponies = function () {
  const settings = Backdrop.settings.konamicode?.browserponies;

  console.log('Browser Ponies settings:', settings);

  if (!settings) {
    console.error('Browser Ponies settings are missing.');
    return;
  }

  // Ensure the baseurl ends with a slash
  let baseUrl = settings.baseurl || '';
  if (!baseUrl.endsWith('/')) {
    baseUrl += '/';
  }
  const scriptUrl = `${baseUrl}/browserponies.js`;
  const configUrl = `${baseUrl}/basecfg.js`;

  // Map the configuration keys to the names expected by Browser Ponies.
  const ponyNameMap = {
    pinkiepie: 'Pinkie Pie',
    rainbowdash: 'Rainbow Dash',
    twilightsparkle: 'Twilight Sparkle',
    applejack: 'Applejack',
    fluttershy: 'Fluttershy',
    rarity: 'Rarity',
  };

  const spawnConfig = {};
  for (const [key, value] of Object.entries(settings)) {
    if (ponyNameMap[key] && value > 0) {
      spawnConfig[ponyNameMap[key]] = value; // Map the pony names.
    }
  }

  // Dynamically load the Browser Ponies script and configuration.
  jQuery.getScript(configUrl, function () {
    console.log('BrowserPonies base configuration loaded.');

    jQuery.getScript(scriptUrl, function () {
      console.log('BrowserPonies script loaded.');

      if (typeof BrowserPonies === 'undefined') {
        console.error('BrowserPonies library did not load correctly.');
        return;
      }

      // Initialize Browser Ponies.
      BrowserPonies.setBaseUrl(baseUrl);

      // Load configuration.
      BrowserPonies.loadConfig(BrowserPoniesBaseConfig); // Default configuration.
      BrowserPonies.loadConfig({
        fadeDuration: settings.fade_duration,
        volume: settings.volume,
        fps: settings.fps,
        speed: settings.speed,
        audioEnabled: settings.audio_enabled,
        showFps: settings.show_fps,
        showLoadProgress: settings.show_load_progress,
        speakProbability: settings.speak_probability,
        spawn: spawnConfig, // Use the mapped spawn configuration.
      });

      console.log('Browser Ponies initialized successfully with spawn config:', spawnConfig);
      console.log('Autostart is enabled. Starting Browser Ponies...');
      BrowserPonies.start();
    });
  });
};
