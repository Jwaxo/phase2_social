<?php
/**
 * @file
 * Adds meta tags.
 */

/**
 * Adds open graph meta tags to the head.
 *
 * @param object $node
 *   The node from context.
 */
function phase2_social_open_graph($node) {
  global $base_url;
  $title = $node->title;
  if (!isset($title)) {
    $title = drupal_get_title();
  }
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
  // OpenGraph meta tags.
  $opengraph = array(
    // Node title.
    'og_title' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:title',
        'content' => filter_xss(trim($title)),
      ),
      '#weight' => -99.8,
    ),
    // Site name.
    'og_site_name' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:site_name',
        'content' => 'Catholic Relief Services',
      ),
      '#weight' => -99.7,
    ),
    // Url.
    'og_url' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:url',
        'content' => $base_url . request_uri(),
      ),
      '#weight' => -99.6,
    ),
    'og_type' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:type',
        'content' => 'article',
      ),
      '#weight' => -99.5,
    ),
    'article_published' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'article:published_time',
        'content' => format_date($node->created, 'custom', 'Y-m-dTH:iZ'),
      ),
      '#weight' => -99.5,
    ),
    'article_changed' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'article:modified_time',
        'content' => format_date($node->changed, 'custom', 'Y-m-dTH:iZ'),
      ),
      '#weight' => -99.5,
    ),
    'og_description' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:description',
        'content' => isset($description) ? $description : '',
      ),
      '#weight' => -99.4,
    ),
  );
  foreach ($opengraph as $key => $data) {
    drupal_add_html_head($data, $key);
  }

  // @todo: Really should have an image on the node.
  // From LinkedIn:
  // For the highest quality presentation on LinkedIn.com, the image referenced
  // in og:image should be at least 80 x 150px to prevent it from being
  // artificially stretched to fit the layout.

  // @todo: Do we need Twitter tags?.
}
