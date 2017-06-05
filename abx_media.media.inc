<?php 
/**
 * Implements hook_theme().
 */
function abx_media_theme() {
  return array(
    'file_entity' => array(
      'render element' => 'elements',
      'template' => 'file_entity',
    ),
    'file_entity_simple_link' => array(
      'variables' => array('file' => NULL, 'icon_directory' => NULL, 'text' => NULL),
    ),
  );
}
/**
 * @file
 * Field API integration for the file_entity module.
 */

/**
 * Implements hook_field_formatter_info().
 */
function abx_media_field_formatter_info() {
  $info['file_simple_link'] = array(
    'label' => t('Simple link'),
    'description' => t('Just a link. Nothing else.'),
    'field types' => array('file', 'image'),
    'settings' => array(
      'text' => t('[file:name]'),
    ),
  );
  return $info;
}


/**
 * Implements hook_field_formatter_settings_form().
 */
function abx_media_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  if ($display['type'] == 'file_simple_link') {
    $element['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link text'),
      '#description' => t('This field support tokens.'),
      '#default_value' => $settings['text'],
      '#required' => TRUE,
    );
  }
  

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function abx_media_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = array();

  if ($display['type'] == 'file_simple_link') {
    $summary[] = t('Link text: %text', array('%text' => $settings['text']));
  }
  

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function abx_media_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  switch ($display['type']) {
    case 'file_simple_link':
      foreach ($items as $delta => $item) {
        $file = (object) $item;
        if (file_entity_access('download', $file)) {
          $element[$delta] = array(
            '#theme' => 'file_entity_simple_link',
            '#file' => $file,
            '#text' => $settings['text'],
          );
        }
      }
      break;

    
  }

  return $element;
}

/**
 * Copy of theme_file_link() for linking to the file download URL.
 *
 * @see theme_file_link()
 */
function theme_file_entity_simple_link($variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $uri = file_entity_download_uri($file);
  $icon = theme('file_icon', array('file' => $file, 'icon_directory' => $icon_directory));

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $uri['options']['attributes']['type'] = $file->filemime . '; length=' . $file->filesize;
  $uri['options']['attributes']['class'] = 'file-download';

  // Provide the default link text.
  if (!isset($variables['text'])) {
    $variables['text'] = t('[file:name]');
  }

  // Perform unsanitized token replacement if $uri['options']['html'] is empty
  // since then l() will escape the link text.
  $variables['text'] = token_replace($variables['text'], array('file' => $file), array('clear' => TRUE, 'sanitize' => !empty($uri['options']['html'])));

  $output =  l($variables['text'], $uri['path'], $uri['options']);

  return $output;
}