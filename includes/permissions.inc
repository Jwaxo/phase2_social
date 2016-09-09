<?php

/**
 * @file
 */

/**
 * Implements hook_permission().
 */
function phase2_social_permission() {
  return array(
    'administer phase2 social' => array(
      'title' => t('Administer Phase2 Social'),
      'description' => t('Configure settings related to social sharing.'),
    ),
  );
}
