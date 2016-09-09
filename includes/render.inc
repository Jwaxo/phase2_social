<?php
/**
 * @file
 * Social widget render functions.
 */

include_once 'meta.inc';
include_once 'callbacks.inc';

/**
 * Social widget rendering helper.
 *
 * @param object $node
 *   The node from context.
 * @param array $data
 *   The data as returned from hook_social_info().
 *
 * @return string
 *   Rendered markup.
 */
function phase2_social_widget_render($node, $data, $network) {
  $build = array();

  // Add meta tags.
  $meta_function = 'phase2_social_' . $network . '_tags';
  if (function_exists($meta_function)) {
    $meta_function($node);
  }

  $elements = element_children($data);
  foreach ($elements as $element) {
    // Ignore callbacks.
    if ($element !== 'variables') {
      $build[$element] = $data[$element];
    }
  }

  foreach ($data['variables'] as $key => $callback) {
    $variable = str_replace('-', '_', $key);
    if (function_exists($callback)) {
      $build[$variable] = $callback($node, $data);
    }
    else {
      $build[$variable] = $callback;
    }
  }
  $build['#theme'] = $data['theme'];

  return render($build);

}

function phase2_social_twitter_share_message($node, $data) {
  return phase2_social_share_message($node, 50);
}
