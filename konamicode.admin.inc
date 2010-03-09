<?php
// $Id$

/**
 * @file
 * Provides the administration settings for the Konami Code module.
 */

/**
 * Menu callback; The administration settings for the Konami Code.
 */
function konamicode_admin_settings() {
  // Retrieve all available Konami Actions.
  $actions = module_invoke_all('konamicode');

  // Allow the user to choose which actions are active.
  $enabled = array_filter(variable_get('konamicode_actions', array()));
  // The default requires at least Image Attack.
  if (empty($enabled)) {
    $enabled = array('imageattack' => 'imageattack');
  }
  $form['konamicode_actions'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Actions'),
    '#description' => t('Which actions should be enabled.'),
    '#options' => $actions,
    '#default_value' => $enabled,
  );

  // Settings for each individual action.
  foreach ($actions as $action => $name) {
    $settings = module_invoke_all('konamicode_' . $action . '_settings');
    $settings['konamicode_code_' . $action] = array(
      '#type' => 'textfield',
      '#title' => t('Key code sequence'),
      '#default_value' => variable_get('konamicode_code_' . $action, '38,38,40,40,37,39,37,39,66,65'),
      '#description' => t('The <a href="@keycodes">JavaScript key code sequence</a> used to activate the %name action, seperated by commas. Defaults to the <a href="@konamicode">Konami Code</a>.', array('%name' => $name, '@konamicode' => 'http://en.wikipedia.org/wiki/Konami_code', '@keycodes' => 'http://www.cambiaresearch.com/c4/702b8cd1-e5b0-42e6-83ac-25f0306e3e25/javascript-char-codes-key-codes.aspx')),
      '#weight' => -9,
    );
    $form['konamicode_action_' . $action] = array_merge($settings, array(
      '#type' => 'fieldset',
      '#title' => $name,
      '#collapsible' => TRUE,
      '#collapsed' => isset($enabled[$action]) ? $enabed[$action] == $enabled[$action] : TRUE,
    ));
  }
  return system_settings_form($form);
}


/**
 * Settings for the Konami Code Image Attack action.
 */
function konamicode_konamicode_imageattack_settings() {
  $form['konamicode_imageattack'] = array(
    '#title' => t('Images'),
    '#type' => 'textarea',
    '#description' => t('The absolute URL of the images to attack the user with. Each different image should be seperated by a line break.'),
    '#default_value' => variable_get('konamicode_imageattack', 'http://drupalcode.org/viewvc/drupal/contributions/docs/marketing/logo/druplicon.small.png?view=co'),
    '#rows' => 2,
  );
  return $form;
}

/**
 * Settings for the Konami Code Redirect action.
 */
function konamicode_konamicode_redirect_settings() {
  $form['konamicode_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination'),
    '#description' => t('When people enter the <a href="@konamicode">Konami Code</a>, redirect them to the given URL. This can either be an internal or external path.', array('@konamicode' => 'http://en.wikipedia.org/wiki/Konami_code')),
    '#default_value' => variable_get('konamicode_destination', 'http://bacolicio.us/http://' . $_SERVER['SERVER_NAME'] . base_path()),
  );
  return $form;
}

/**
 * Settings for the Konami Code Alert action.
 */
function konamicode_konamicode_alert_settings() {
  $form['konamicode_alert'] = array(
    '#type' => 'textfield',
    '#title' => t('Text'),
    '#description' => t('The text to display to the user.'),
    '#default_value' => variable_get('konamicode_alert', t('Konami Code is geek!')),
  );
  return $form;
}
