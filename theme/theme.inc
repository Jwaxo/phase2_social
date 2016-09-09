<?php

/**
 * @file
 */

/**
 * Using a helper for now.
 *
 * Leaving the individual preprocess functions for context.
 */
function phase2_social_pre_render(&$vars) {
  $element = &$vars['element'];
  foreach ($element['class'] as $class) {
    $vars['classes_array'][] = $class;
  }
  if ($element['style'] === 'vertical') {
    $vars['classes_array'][] = 'vertical';
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function phase2_social_preprocess_phase2_social_widget(&$vars) {
  $module = drupal_get_path('module', 'phase2_social');
  drupal_add_css($module . '/css/phase2_social.css');
}

/**
 * Implements hook_preprocess_HOOK().
 */
function phase2_social_preprocess_phase2_social_widget_facebook(&$vars) {
  phase2_social_pre_render($vars);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function phase2_social_preprocess_phase2_social_widget_twitter(&$vars) {
  $vars['description'] = '';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function phase2_social_preprocess_phase2_social_widget_linkedin(&$vars) {
  phase2_social_pre_render($vars);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function phase2_social_preprocess_phase2_social_widget_email(&$vars) {
  phase2_social_pre_render($vars);
}
