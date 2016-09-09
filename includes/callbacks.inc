<?php
/**
 * @file
 * Additional logic for social widgets.
 */

/**
 * Helper used to truncate the node body/description.
 *
 * @param object $node
 *   The node from context.
 * @param int $limit
 *   Character limit.
 *
 * @return string
 *   The description used in the popup.
 */
function phase2_social_share_message($node, $limit = 100) {
  // Entity metadata wrapper.
  $wrapper = entity_metadata_wrapper('node', $node);

  // Build a description from the body text.
  $description = $wrapper->body->value()['safe_value'];
  $description = drupal_html_to_text($description);
  $description = truncate_utf8($description, $limit, TRUE, TRUE, 8);
  return $description;
}

/**
 * Helper to build a title.
 *
 * @param $node
 *
 * @return string
 */
function phase2_social_share_title($node) {

  $title = '';

  // It's possible that the node title is being set from page manager.
  if (!isset($node->title) && module_exists('page_manager')) {
    $page = page_manager_get_current_page();
    if (!empty($page)) {
      $title = $page['contexts'][$page['handler']->conf['context']]->title;
    }
  }
  else {
    $title = $node->title;
  }

  return $title;
}

/**
 * Helper to find a default image.
 *
 * @return string
 *   Path to image.
 */
function phase2_social_share_image() {

  // Check for an uploaded image.
  if ($image = variable_get('p2_social_default_image_file', FALSE)) {
    return $image;
  }

  // If no default image was uploaded.
  if (!isset($image)) {
    // Check for a logo to use as the default image.
    $theme = variable_get('theme_default', FALSE);
    if ($theme) {
      $settings = variable_get('theme_' . $theme . '_settings', FALSE);
      if ($settings && isset($settings['logo_path'])) {
        if (isset($settings['logo_path']) && !empty($settings['logo_path'])) {
          $image = file_uri_to_object($settings['logo_path']);
        }
        elseif (isset($settings['default_logo']) && !empty($settings['default_logo']))
          $image = file_uri_to_object($settings['default_logo']);
      }
    }
  }

  return $image;
}

/**
 * Helper that returns the share url.
 *
 * @param object $node
 *   The node in context.
 *
 * @return string
 *   The current path.
 */
function phase2_social_share_url($node, $data) {
  // @todo: Use something like: https://www.drupal.org/project/shurly.
  global $base_url;
  return $base_url . '/' . request_path();
}
