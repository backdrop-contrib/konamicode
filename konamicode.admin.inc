<?php
/**
 * @file
 * Provides the administration settings for the Konami Code module.
 */

/**
 * Menu callback: Settings form for the Konami Code module.
 */
function konamicode_admin_settings($form, &$form_state) {
  $form = [];
  $form['#config'] = 'konamicode.settings';

  $name = 'Konami Code';

  // Main toggle for enabling/disabling the module.
  $form['konamicode_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_enabled')
  ?? 1,
    '#description' => t('Allows you to completely disable the Konami Code module disregarding the separate Action statuses.'),
  ];

  // Vertical tabs for actions.
  $form['konamicode_actions'] = [
    '#type' => 'vertical_tabs',
    '#title' => t('Actions'),
  ];

  // Image Attack Settings.
  $form['imageSpawn'] = [
    '#type' => 'fieldset',
    '#title' => t('Image Spawn'),
    '#group' => 'konamicode_actions',
    '#description' => t('Will spawn a given amount of images on the screen when the Konami Code is entered.'),
  ];
  $form['imageSpawn']['konamicode_imageSpawn_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_imageSpawn_enabled') ?? 0,
  ];
  $form['imageSpawn']['konamicode_imageSpawn_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_imageSpawn_keycode_sequence') ??
      '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['imageSpawn']['konamicode_imageSpawn_images'] = [
    '#type' => 'textarea',
    '#title' => t('Images'),
    '#description' => t('The absolute URL of the images to attack the user with. Each different image should be separated by a line break.'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_imageSpawn_images') ?? '',
    '#rows' => 2,
  ];
  $form['imageSpawn']['konamicode_imageSpawnmax'] = [
    '#type' => 'textfield',
    '#title' => t('Amount of images'),
    '#description' => t('Number of images to appear on the screen during an attack.'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_imageSpawnmax') ?? '',
    '#size' => 5,
  ];

  // Redirect settings.
  $form['redirect'] = [
    '#type' => 'fieldset',
    '#title' => t('Redirect'),
    '#group' => 'konamicode_actions',
    '#description' => t('Redirect users to a given destination URL when the Konami Code is entered.'),
  ];
  $form['redirect']['konamicode_redirect_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_redirect_enabled') ?? 0,
  ];
  $form['redirect']['konamicode_redirect_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_redirect_keycode_sequence') ??
    '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['redirect']['konamicode_redirect_destination'] = [
    '#type' => 'textfield',
    '#title' => t('Destination'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_redirect_destination') ?? '',
    '#description' => t('The URL to redirect users to after the Konami Code is entered.'),
  ];

  // Alert settings.
  $form['alert'] = [
    '#type' => 'fieldset',
    '#title' => t('Alert'),
    '#group' => 'konamicode_actions',
    '#description' => t('Will open a "classic" alert window with a predefined message when the Konami Code is entered.'),
  ];
  $form['alert']['konamicode_alert_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_alert_enabled') ?? 0,
  ];
  $form['alert']['konamicode_alert_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_alert_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['alert']['konamicode_alert_message'] = [
    '#type' => 'textfield',
    '#title' => t('Message'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_alert_message') ?? '',
    '#description' => t('The message to display when the Konami Code is entered.'),
  ];

  // Flip Text settings.
  $form['fliptext'] = [
    '#type' => 'fieldset',
    '#title' => t('Flip Text'),
    '#group' => 'konamicode_actions',
    '#description' => t('Will flip all the text on the page around when the Konami Code is entered.'),
  ];
  $form['fliptext']['konamicode_fliptext_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_fliptext_enabled') ?? 0,
  ];
  $form['fliptext']['konamicode_fliptext_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_fliptext_keycode_sequence') ??
    '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  // Cornify settings
  $form['cornify'] = [
    '#type' => 'fieldset',
    '#title' => t('Cornify'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the Cornify action.'),
  ];
  $form['cornify']['konamicode_cornify_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_cornify_enabled') ?? 0,
  ];
  $form['cornify']['konamicode_cornify_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_cornify_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  //Geocities-izer
  $form['geocitiesizer'] = [
    '#type' => 'fieldset',
    '#title' => t('Geocities-izer'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the Geocities-izer action.  <br> <strong>NOTE:</strong> This is a very old action relying on an external HTTP site. This will not work on sites using https.'),
  ];
  $form['geocitiesizer']['konamicode_geocitiesizer_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_geocitiesizer_enabled') ?? 0,
  ];
  $form['geocitiesizer']['konamicode_geocitiesizer_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_geocitiesizer_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['geocitiesizer']['konamicode_geocitiesizer_theme'] = [
    '#type' => 'select',
    '#title' => t('Theme'),
    '#description' => t('The theme to use when Geocities-izing.'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_geocitiesizer_theme'),
    '#options' => array(
      0 => t('Random'),
      1 => t('Yellow'),
      2 => t('Tech'),
      3 => t('Space'),
    ),
  ];

  // Asteroids settings
  $form['asteroids'] = [
    '#type' => 'fieldset',
    '#title' => t('Asteroids'),
    '#group' => 'konamicode_actions',
    '#description' => t('Will allow you to destroy the page "asteroids" style when the Konami Code is entered.'),
  ];
  $form['asteroids']['konamicode_asteroids_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_asteroids_enabled') ?? 0,
  ];
  $form['asteroids']['konamicode_asteroids_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_asteroids_keycode_sequence')
    ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  // Replace Images settings
  $form['replaceImages'] = [
    '#type' => 'fieldset',
    '#title' => t('Replace Images'),
    '#group' => 'konamicode_actions',
    '#description' => t('Will replace all images on the page with placeholder images from the configured sources when the Konami Code is entered.'),
  ];
  $form['replaceImages']['konamicode_replaceImages_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_replaceImages_enabled') ?? 0,
  ];
  $form['replaceImages']['konamicode_replaceImages_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_replaceImages_keycode_sequence')
    ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['replaceImages']['konamicode_replaceImages_integrations'] = [
    '#type' => 'checkboxes',
    '#title' => t('Integrations'),
    '#description' => t('Select the image sources you want to use. If you select multiple, images will be replaced at random.'),
    '#options' => [
      'baby' => t('Baby'),
      'bacon' => t('Bacon'),
      'bear' => t('Bear'),
      'beer' => t('Beer'),
      'nicolas_cage' => t('Nicolas Cage'),
      'geese' => t('Geese'),
      'cats' => t('cats'),
      'lorem_picsum' => t('Lorem Picsum'),
      'lorem_pixel' => t('Lorem Pixel'),
    ],
    '#default_value' => config_get('konamicode.settings', 'konamicode_replaceImages_integrations') ?? [],
  ];

  // Raptorize settings
  $form['raptorize'] = [
    '#type' => 'fieldset',
    '#title' => t('Raptorize'),
    '#group' => 'konamicode_actions',
    '#description' => t('An Velociraptor from Jurassic Park will attack the screen when the Konami Code is entered.'),
  ];
  $form['raptorize']['konamicode_raptorize_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_raptorize_enabled') ?? 0,
  ];
  $form['raptorize']['konamicode_raptorize_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_raptorize_keycode_sequence')
    ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  // Katamari Hack settings
  $form['katamari'] = [
    '#type' => 'fieldset',
    '#title' => t('Katamari Hack'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the Katamari Hack action.'),
  ];
  $form['katamari']['konamicode_katamari_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_katamari_enabled') ?? 0,
  ];
  $form['katamari']['konamicode_katamari_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_katamari_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  // Snowfall settings.
  $form['snowfall'] = [
    '#type' => 'fieldset',
    '#title' => t('Snowfall'),
    '#group' => 'konamicode_actions',
    '#description' => t('Will make it snow when the Konami Code is entered. WARNING: setting extreme parameters might make the browser crash. Make sure to test thoroughly before going public.')
  ];
  $form['snowfall']['konamicode_snowfall_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_enabled') ?? 0,
  ];
  $form['snowfall']['konamicode_snowfall_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_keycode_sequence') ??
    '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['snowfall']['konamicode_snowfall_flake_count'] = [
    '#type' => 'textfield',
    '#title' => t('Flake count'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_flake_count') ?? '35',
  ];
  $form['snowfall']['konamicode_snowfall_flake_color'] = [
    '#type' => 'textfield',
    '#title' => t('Flake color'),
    '#default_value' => config_get('konamicode.settings','konamicode_snowfall_flake_color') ?? '#ffffff',
  ];
  $form['snowfall']['konamicode_snowfall_minsize'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum Size'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_minsize'),
  ];
  $form['snowfall']['konamicode_snowfall_maxsize'] = [
    '#type' => 'textfield',
    '#title' => t('Maximum Size'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_maxsize'),
  ];
  $form['snowfall']['konamicode_snowfall_minspeed'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum Speed'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_minspeed'),
  ];
  $form['snowfall']['konamicode_snowfall_maxspeed'] =[
    '#type' => 'textfield',
    '#title' => t('Maximum Speed'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_maxspeed'),
  ];
  $form['snowfall']['konamicode_snowfall_round'] = [
    '#type' => 'checkbox',
    '#title' => t('Round'),
    '#description' => t('Makes the snowflakes rounded if the browser supports it.'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_round'),
  ];
  $form['snowfall']['konamicode_snowfall_shadow'] = [
    '#type' => 'checkbox',
    '#title' => t('Shadow'),
    '#description' => t('Gives the snowflakes a shadow if the browser supports it.'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_snowfall_shadow'),
  ];

  // GG settings
  $form['gg'] = [
    '#type' => 'fieldset',
    '#title' => t('GG'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the GG action.'),
  ];
  $form['gg']['konamicode_gg_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_gg_enabled') ?? 0,
  ];
  $form['gg']['konamicode_gg_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_gg_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  // Browser Ponies settings
  $form['browserponies'] = [
    '#type' => 'fieldset',
    '#title' => t('Browser Ponies'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the Katamari Hack action.'),
  ];
  $form['browserponies']['konamicode_browserponies_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_enabled') ?? 0,
  ];
  $form['browserponies']['konamicode_browserponies_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  $form['browserponies']['konamicode_browserponies_baseurl'] = [
    '#type' => 'textfield',
    '#title' => t('Base URL'),
    '#description' => t('Base URL of the Browser Ponies files'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_baseurl'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_showLoadProgress'] = [
    '#type' => 'checkbox',
    '#title' => t('Show Download Progress Bar'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_showLoadProgress'),
  ];

  $form['browserponies']['konamicode_browserponies_fadeDuration'] = [
    '#type' => 'textfield',
    '#title' => t('Fade Duration'),
    '#description' => t('Amount of time in milliseconds for the ponies to appear on the screen'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_fadeDuration'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_audioEnabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enable audio if browser supports HTML 5 Audio'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_audioEnabled'),
  ];

  $form['browserponies']['konamicode_browserponies_volume'] = [
    '#type' => 'textfield',
    '#title' => t('Audio Volume'),
    '#description' => t('Enter a value between 0 and 1 (eg. 0.1, 0.2, etc)'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_volume'),
  ];

  $form['browserponies']['konamicode_browserponies_fps'] = [
    '#type' => 'textfield',
    '#title' => t('Frames Per Second'),
    '#description' => t('The lower the number, the better the performance'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_fps'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_showFps'] = [
    '#type' => 'checkbox',
    '#title' => t('Show Frames per Second'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_showFps'),
  ];

  $form['browserponies']['konamicode_browserponies_speed'] = [
    '#type' => 'textfield',
    '#title' => t('Speed Multiplier'),
    '#description' => t('How fast are these ponies going?'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_speed'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_speakProbability'] = [
    '#type' => 'textfield',
    '#title' => t('Random Speak Probability'),
    '#description' => t('Enter a value between 0 and 1 (eg. 0.1, 0.2, etc)'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_speakProbability'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_applejack'] = [
    '#type' => 'textfield',
    '#title' => t('Applejack'),
    '#description' => t('Enter the number of Applejack ponies on the screen'),
    '#default_value' => config_get('konamicode.settings','konamicode_browserponies_applejack'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_fluttershy'] = [
    '#type' => 'textfield',
    '#title' => t('Fluttershy'),
    '#description' => t('Enter the number of Fluttershy ponies on the screen'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_fluttershy'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_pinkiepie'] = [
    '#type' => 'textfield',
    '#title' => t('Pinkiepie'),
    '#description' => t('Enter the number of Pinkiepie ponies on the screen'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_pinkiepie'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_rainbowdash'] = [
    '#type' => 'textfield',
    '#title' => t('Rainbowdash'),
    '#description' => t('Enter the number of Rainbowdash ponies on the screen'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_browserponies_rainbowdash'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_rarity'] = [
    '#type' => 'textfield',
    '#title' => t('Rarity'),
    '#description' => t('Enter the number of Rarity ponies on the screen'),
    '#default_value' => config_get('konamicode.settings','konamicode_browserponies_rarity'),
    '#required' => TRUE,
  ];

  $form['browserponies']['konamicode_browserponies_twilightsparkle'] = [
    '#type' => 'textfield',
    '#title' => t('Twilight Sparkle'),
    '#description' => t('Enter the number of Twilight Sparkle ponies on the screen'),
    '#default_value' => config_get('konamicode.settings','konamicode_browserponies_twilightsparkle'),
    '#required' => TRUE,
  ];

  // Cheetos Font
  $form['cheetosfont'] = [
    '#type' => 'fieldset',
    '#title' => t('Cheetos Font'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the <a href="@cheetosfont">Cheetos Font</a> action.  The first font fully designed with the other hand.', array(
      '%name' => $name,
      '@cheetosfont' => 'https://www.cheetos.com/otherhand',
    )),
  ];
  $form['cheetosfont']['konamicode_cheetosfont_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_cheetosfont_enabled') ?? 0,
  ];
  $form['cheetosfont']['konamicode_cheetosfont_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_cheetosfont_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];

  // Airplane settings
  $form['airplane'] = [
    '#type' => 'fieldset',
    '#title' => t('Airplane'),
    '#group' => 'konamicode_actions',
    '#description' => t('Settings associated with the Airplane action.'),
  ];
  $form['airplane']['konamicode_airplane_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_airplane_enabled') ?? 0,
  ];
  $form['airplane']['konamicode_airplane_keycode_sequence'] = [
    '#type' => 'textfield',
    '#title' => t('Key code sequence'),
    '#default_value' => config_get('konamicode.settings', 'konamicode_airplane_keycode_sequence') ?? '',
    '#description' => t('The <a href="@keycodes">key code sequence</a> used to activate the %name action, seperated by commas. Provide either the key code integer, or the character of the key. Defaults to the <a href="@konamicode">Konami Code</a>. Some examples are: "<em>38,38,40,40,37,39,37,39,66,65</em>", "<em>g,o,d</em>", "<em>n,o,c,l,i,p</em>", etc.', array(
      '%name' => $name,
      '@konamicode' => 'https://github.com/backdrop-contrib/konamicode/wiki/General-Information-and-History',
      '@keycodes' => 'https://github.com/backdrop-contrib/konamicode/wiki/Configuring-Key-Code-Sequence',
    )),
  ];
  return system_settings_form($form);
}
