<?php

/**
 * Implements hook_field_views_data().
 */
function field_uconnect_license_field_views_data($field) {
  $data = field_views_field_default_views_data($field);


  // Only expose these components as Views field handlers.
  $implemented = array(
    'field_uconnect_license_name' => 'views_handler_field',
    'field_uconnect_license_url' => 'views_handler_field',
    'field_uconnect_license_explanation' => 'views_handler_field',
    'field_uconnect_license_properties_1' => 'views_handler_field',
    'field_uconnect_license_properties_2' => 'views_handler_field',
    'field_uconnect_license_properties_3' => 'views_handler_field',
    'field_uconnect_license_properties_4' => 'views_handler_field',
    'field_uconnect_license_properties_5' => 'views_handler_field',
  );

  // Get the translated field information.
  $properties = field_uconnect_license_data_property_info();

  // Iterate over addressfield defined tables.
  foreach ($data as &$table) {
    // Make sure the parent Views field (filed_uconnect_license) is defined.
    if (isset($table[$field['field_name']]['field'])) {
      // Use the parent field definition as a template for component columns.
      $field_def = $table[$field['field_name']]['field'];

      // Remove 'additional fields' from the field definition. We don't
      // necessarily want all our sibling columns.
      unset($field_def['additional fields']);

      // Define the valid columns.
      $valid_columns = array();
      foreach ($implemented as $implement => $handler) {
        $column_name = $field['field_name'] . '_' . $implement;
        $valid_columns[$column_name] = $handler;
      }

      // Iterate over the field_uconnect_license components.
      foreach ($table as $column_name => &$column) {
        if (empty($column['field']) && isset($valid_columns[$column_name])) {
          // Assign the default component definition.
          $column['field'] = $field_def;
          $column['field']['real field'] = $column_name;
          $column['field']['handler'] = $valid_columns[$column_name];

          // Assign human-friendly field labels for addressfield components.
          $field_labels = field_views_field_label($field['field_name']);
          $field_label = array_shift($field_labels);
          $property = str_replace($field_def['field_name'] . '_', '', $column_name);

          if (!empty($properties[$property])) {
            $property_label = $properties[$property]['label'];

            $title = t('@field-label - @property-label', array(
              '@field-label' => $field_label,
              '@property-label' => $property_label,
            ));

            $column['title'] = $title;
            $column['title short'] = $title;
          }
        }
      }
    }
  }

  return $data;
}
