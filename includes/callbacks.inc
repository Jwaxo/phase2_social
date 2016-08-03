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
 *
 * @return string
 *   The description used in the popup.
 */
function phase2_social_truncate_description($node) {
  $description = '';
  // Entity metadata wrapper.
  $wrapper = entity_metadata_wrapper('node', $node);
  // Get the value of the body field.
  $body = $wrapper->body->value()['value'];
  $format = $wrapper->body->value()['format'];
  if (!empty($body)) {
    // This gets a decent summary using <p></p> tags to find break points.
    // This ensures that a word isn't cut off in the middle and potentially
    // display an unintended word :). As long as we give it enough length.
    $summary = text_summary($body, $format, 350);
    // Now we can strip the html tags.
    $description = strip_tags($summary);
  }
  return $description;
}

/**
 * Helper that returns the share message.
 *
 * @param object $node
 *   The node in context.
 *
 * @return string
 *   A description of the node.
 */
function phase2_social_share_message($node, $data) {
  $description = phase2_social_truncate_description($node);
  return urlencode($description);
}
/**
 * Helper that returns the share message for twitter.
 *
 * @todo: Actually use this and make sure we are under the character limit.
 *
 * @param object $node
 *   The node in context.
 *
 * @return string
 *   A description of the node.
 */
function phase2_social_share_twitter_message($node, $data) {
  $description = phase2_social_truncate_description($node);
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
  return urlencode($base_url . '/' . request_path());
}

/**
 * Helper that returns the share title.
 *
 * @param object $node
 *   The node in context.
 *
 * @return string
 *   The title of the node.
 */
function phase2_social_share_title($node, $data) {
  return urlencode($node->title);
}
