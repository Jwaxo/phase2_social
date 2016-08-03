<?php
/**
 * @file
 * Create a widget for social links.
 */

$plugin = array(
  'title' => t('Social Widget'),
  'description' => t('A widget that allows adding social links.'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => array(t('Widgets'), -9),
  'hook theme' => 'phase2_social_social_widget_content_type_theme',
  'templates' => 'theme',
  'template prefix' => 'social-widget',
  'defaults' => array(
    'style' => NULL,
    'networks' => array(),
  ),
);

/**
 * The widget configuration form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 *
 * @return mixed
 *   The form.
 */
function phase2_social_social_widget_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['style'] = array(
    '#type' => 'select',
    '#title' => t('Style'),
    '#options' => drupal_map_assoc(phase2_social_social_widget_content_type_styles()),
    '#default_value' => $conf['style'],
  );

  // Build options for checkboxes.
  $info = phase2_social_widgets_info();
  $options = array();
  foreach ($info as $network => $data) {
    $options[$network] = $data['title'];
  }
  $form['networks'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select Networks'),
    '#options' => $options,
    '#default_value' => $conf['networks'],
  );
  return $form;
}

/**
 * The widget configuration form submit.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function phase2_social_social_widget_content_type_edit_form_submit($form, &$form_state) {

  foreach(array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Renders the widget.
 *
 * @param string $subtype
 *   This widget is the only type.
 * @param array $conf
 *   Configuration as done at admin time
 * @param array $args
 *   Extra arguments passed in the pane.
 * @param object $context
 *   Context - in this case we expect a node.
 *
 * @return \stdClass
 *   A block suitable for rendering.
 */
function phase2_social_social_widget_content_type_render($subtype, $conf, $args, $context) {

  if (!empty($context) && empty($context->data)) {
    return;
  }
  if (!isset($conf['networks'])) {
    return;
  }
  // Networks that have been enabled.
  $networks = array_filter($conf['networks']);
  // Get info about all social links.
  $social_info = phase2_social_widgets_info();

  $shares = array();
  $module = drupal_get_path('module', 'phase2_social');

  foreach ($networks as $network) {
    $data = $social_info[$network];
    $data['style'] = $conf['style'];

    if (isset($data['render']) && function_exists($data['render'])) {
      $shares[$network]['#type'] = '#markup';
      $shares[$network] = $data['render']($context->data, $data);
    }
  }

  $content = array(
    '#theme' => 'phase2_social_widget',
    '#node' => $context->data,
    '#shares' => $shares,
    '#attached' => array(
      'js' => array(
        $module . '/js/phase2_social.js' => array(
          'scope' => 'header',
          'type' => 'file',
        ),
      ),
    ),
  );

  $block = new stdClass();
  $block->title = '';
  $block->content = $content;

  return $block;
}

/**
 * Defines styles that will require a template file.
 *
 * After defining a new style, add a template for the style.
 *
 * @see phase2_social_social_widget_content_type_theme()
 *
 * @return array
 *   Names of styles.
 */
function phase2_social_social_widget_content_type_styles() {
  return array(
    'horizontal',
    'vertical',
  );
}

/**
 * Defines theme hooks for the widget.
 *
 * @param array $theme
 *   Themes.
 * @param object $plugin
 *   The plugin.
 */
function phase2_social_social_widget_content_type_theme(&$theme, $plugin) {
  $module = drupal_get_path('module', $plugin['module']);
  $path = $module . '/' . $plugin['templates'];
  $theme['phase2_social_widget'] = array(
    'path' => $path,
    'template' => $plugin['template prefix'],
    'variables' => array(
      'shares' => NULL,
      'node' => NULL,
    ),
  );
  // You will need to create a template when adding a new widget. It will
  // be registered here.
  $widgets = phase2_social_social_info();
  foreach ($widgets as $name => $widget) {
    if (isset($widget['theme'])) {
      $theme[$widget['theme']] = array(
        'path' => $path,
        'template' => $plugin['template prefix'] . '-' . $name,
        'render element' => 'element',
      );
    }
  }
}
