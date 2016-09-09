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
function phase2_social_facebook_tags($node) {
  global $base_url;

  $title = phase2_social_share_title($node);

  // Build a description from the body text.
  $description = phase2_social_share_message($node);

  // Try to locate a default image.
  $image = phase2_social_share_image('facebook');

  // Check for an app id.
  $app_id = variable_get('p2_social_facebook_app_id', FALSE);

  // Facebook OG meta tags.
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
        'content' => variable_get('facebook_sitename', variable_get_default('site_name', '')),
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

  // Add the app id if it was set.
  if ($app_id) {
    $opengraph['app_id'] = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'fb:app_id',
        'content' => $app_id,
      ),
      '#weight' => -99.9,
    );
  }

  if (isset($image) && is_object($image)) {
    $opengraph['og_image'] = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'og:image',
        'content' => $image->uri,
      ),
      '#weight' => -99.3,
    );

    $opengraph['og_image_width'] = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:image:width',
        'content' => isset($image->metadata) ? $image->metadata['width'] : '',
      ),
      '#weight' => -99.2,
    );

    $opengraph['og_image_height'] = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'property' => 'og:image:height',
        'content' => isset($image->metadata) ? $image->metadata['height'] : '',
      ),
      '#weight' => -99.1,
    );

  }

  // Allow modification of OG.
  drupal_alter(array('phase2_social', 'phase2_social_facebook_meta'), $opengraph, $node);

  // Add the tags to the head.
  foreach ($opengraph as $key => $data) {
    drupal_add_html_head($data, $key);
  }

}

/**
 * Adds twitter car meta tags to the head.
 *
 * @param object $node
 *   The node from context.
 */
function phase2_social_twitter_tags($node) {
  global $base_url;

  // Grab the title
  $title = phase2_social_share_title($node);

  // Build a description from the body text.
  $description = phase2_social_share_message($node, 50);

  // Try to find a default image.
  $image = phase2_social_share_image('twitter');

  $twitter_tags = array(
    'twitter_card' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'twitter:card',
        'content' => 'summary',
      ),
      '#weight' => -98.9,
    ),
    'twitter_site' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'twitter:site',
        'content' => variable_get('p2_social_twitter_handle', ''),
      ),
      '#weight' => -98.7,
    ),
    'twitter_title' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'twitter:title',
        'content' => $title,
      ),
      '#weight' => -98.6,
    ),
    'twitter_description' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'twitter:description',
        'content' => $description,
      ),
      '#weight' => -98.5,
    ),

  );

  if (isset($image) && is_object($image)) {
    $twitter_tags['twitter_image'] = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'twitter:image',
        'content' => $image->uri,
      ),
      '#weight' => -98.8,
    );
  }

  // Allow modification of the card.
  drupal_alter(array('phase2_social', 'phase2_social_twitter_meta'), $twitter_tags, $node);

  // Add the tags to the head.
  foreach ($twitter_tags as $key => $data) {
    drupal_add_html_head($data, $key);
  }

}

/**
 * Adds pintrest meta tags to the head.
 *
 * @param object $node
 *   The node from context.
 */
function phase2_social_pintrest_tags($node) {
  $verification = variable_get('p2_social_pintrest_id', '');

  $pintrest_tags = array(
    'domain_verify' => array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'p:domain_verify',
        'content' => !empty($verification) ? $verification : '',
      ),
      '#weight' => -97.9,
    ),
  );

  // Allow modification of the card.
  drupal_alter(array('phase2_social', 'phase2_social_pintrest_meta'), $pintrest_tags, $node);

  // Add the tags to the head.
  foreach ($pintrest_tags as $key => $data) {
    drupal_add_html_head($data, $key);
  }
}

/**
 * Adds linked in meta tags to the head.
 *
 * They use the same tags as facebook.
 *
 * @param object $node
 *   The node from context.
 */
function phase2_social_linkedin_tags($node) {
  phase2_social_facebook_tags($node);
}
