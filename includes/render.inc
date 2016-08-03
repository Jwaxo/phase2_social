<?php
/**
 * @file
 * Social widget render functions.
 */

/**
 * Social render helper.
 *
 * @param object $node
 *   The node from context.
 * @param array $data
 *   The data as returned from hook_social_info().
 *
 * @return string
 *   Rendered markup.
 */
function phase2_social_widget_facebook_render($node, $data) {
  return phase2_social_widget_render($node, $data);
}

/**
 * Social render helper.
 *
 * @param object $node
 *   The node from context.
 * @param array $data
 *   The data as returned from hook_social_info().
 *
 * @return string
 *   Rendered markup.
 */
function phase2_social_widget_twitter_render($node, $data) {
  return phase2_social_widget_render($node, $data);
}

/**
 * Social render helper.
 *
 * @param object $node
 *   The node from context.
 * @param array $data
 *   The data as returned from hook_social_info().
 *
 * @return string
 *   Rendered markup.
 */
function phase2_social_widget_linkedin_render($node, $data) {
  return phase2_social_widget_render($node, $data);
}

/**
 * Social render helper.
 *
 * @param object $node
 *   The node from context.
 * @param array $data
 *   The data as returned from hook_social_info().
 *
 * @return string
 *   Rendered markup.
 */
function phase2_social_widget_email_render($node, $data) {
  return phase2_social_widget_render($node, $data);
}

/**
 * Social render helper.
 *
 * @param object $node
 *   The node from context.
 * @param array $data
 *   The data as returned from hook_social_info().
 *
 * @return string
 *   Rendered markup.
 */
function phase2_social_widget_render($node, $data) {
  $build = array();

  $elements = element_children($data);
  foreach ($elements as $element) {
    // Ignore callbacks.
    if ($element !== 'variables') {
      $build["$element"] = $data[$element];
    }
  }

  foreach ($data['variables'] as $key => $var) {
    $variable = str_replace('-', '_', $key);
    if (function_exists($var)) {
      $build["$variable"] = $var($node, $data);
    }
    else {
      $build["$variable"] = $var;
    }
  }

  $build['#theme'] = $data['theme'];

  return render($build);
}
