<?php

/**
 * @file
 */

/**
 * Builds an administrative settings form.
 *
 * @todo Build an api for adding other social networks to the settings form.
 */
function phase2_social_settings_form($form, &$form_state) {

  $form['social_tabs'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-default',
    '#attributes' => array('class' => array('phase2-social')),
  );

  $form['social_tabs']['default'] = phase2_social_default_fieldset($form_state);

  // Get info for all defined widgets.
  $info = phase2_social_widgets_info();

  // A social widget can define a function that will add settings to the
  // settings fieldset.
  foreach ($info as $network => $data) {
    if (isset($data['settings']) && function_exists($data['settings'])) {
      $form['social_tabs'][$network] = $data['settings']($form_state);
    }
  }

  $settings_form = system_settings_form($form);

  // Add our own submit function.
  array_unshift($settings_form['#submit'], 'phase2_social_settings_form_submit');

  return $settings_form;
}

function phase2_social_settings_form_submit($form, &$form_state) {
  // Clear static cache on form submission.
  drupal_static_reset('phase2_social_widgets_info');
}

/**
 * Fieldset builder for the module settings form.
 */
function phase2_social_default_fieldset(&$form_state) {

  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#description' => t('Configure settings for each social network.'),
    '#tree' => FALSE,
  );

  return $fieldset;
}

/**
 * Builds a fieldset for Facebook.
 */
function phase2_social_facebook_fieldset(&$form_state) {

  $element = 'p2_social_facebook';

  $description = t('Facebook settings');

  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('Facebook'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );

  $fieldset[$element . '_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Enable Facebook Share'),
    '#default_value' => variable_get($element . '_enabled', ''),
  );

  $fieldset[$element . '_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('FB App Id'),
    '#description' => t('Enter your app id if you would like to use it.'),
    '#default_value' => variable_get($element . '_app_id', ''),
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element . '_enabled' . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  $fieldset[$element . '_sitename'] = array(
    '#type' => 'textfield',
    '#title' => t('Site name'),
    '#description' => t('Enter your site name the way you would like Facebook to see it'),
    '#default_value' => variable_get($element . '_sitename', ''),
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element . '_enabled' . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  $fieldset[$element . '_fid'] = array(
    '#title' => t('Image'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
    '#default_value' => variable_get($element . '_fid', ''),
    '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element . '_enabled' . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $fieldset;
}

/**
 * Builds a fieldset for Twitter.
 */
function phase2_social_twitter_fieldset(&$form_state) {

  $element = 'p2_social_twitter';

  $description = t('Twitter settings');

  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('Twitter'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );

  $fieldset[$element . '_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Enable Twitter Share'),
    '#default_value' => variable_get($element . '_enabled', ''),
  );

  $fieldset[$element . '_handle'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Handle'),
    '#description' => t('Enter your Twitter handle. e.g., @myTwitter'),
    '#default_value' => variable_get($element . '_handle', ''),
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element . '_enabled' . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  $fieldset[$element . '_fid'] = array(
    '#title' => t('Image'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
    '#default_value' => variable_get($element . '_fid', ''),
    '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element . '_enabled' . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $fieldset;
}

/**
 * Builds a fieldset for LinkedIn.
 *
 * @todo Update linked in.
 */
function phase2_social_linkedin_fieldset($form_state) {

  $element = 'p2_social_linkedin';

  $description = t('LinkedIn settings');

  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('LinkedIn'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );

  $fieldset[$element . '_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Enable LinkedIn Share'),
    '#default_value' => variable_get($element . '_enabled', ''),
  );

  return $fieldset;
}

/**
 * Builds a fieldset for Pintrest.
 */
function phase2_social_pintrest_fieldset($form_state) {

  $element = 'p2_social_pintrest';

  $description = t('Pintrest settings');

  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('Pintrest'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );

  $fieldset[$element . '_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Enable Pintrest Share'),
    '#default_value' => variable_get($element . '_enabled', ''),
  );

  $help_link = l(t('Getting started'), 'https://business.pinterest.com/en/confirm-your-website', array('absolute' => TRUE));
  $fieldset[$element . '_confirm'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation Code'),
    '#description' => t('Enter your Pintrest confirmation code: !help', array('!help' => $help_link)),
    '#default_value' => variable_get($element . '_confirm', ''),
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element . '_enabled' . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $fieldset;
}

/**
 * Builds a fieldset for email.
 */
function phase2_social_email_fieldset($form_state) {

  $element = 'p2_social_email';

  $description = t('Email settings');

  $fieldset = array(
    '#type' => 'fieldset',
    '#title' => t('Email'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
  );

  $fieldset[$element . '_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Enable Email Share'),
    '#default_value' => variable_get($element . '_enabled', ''),
  );

  return $fieldset;
}
