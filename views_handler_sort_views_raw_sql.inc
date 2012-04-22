<?php

/**
 * A handler to provide a field that is completely custom SQL by the administrator.
 *
 * @ingroup views_field_handlers
 */
class views_handler_sort_views_raw_sql extends views_handler_sort {

  function query() {

    $this->query->add_orderby(NULL, $this->options['raw_sql'], $this->options['order'], 'raw_sql_order');

  } // query

  function option_definition() {

    $options = parent::option_definition();

    // Override the alter text option to never alter the text.
    $options['alter']['contains']['alter_text'] = array('default' => FALSE);

    return $options;

  } // option_definition

  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['raw_sql'] = array(
      '#type' => 'textarea',
      '#title' => 'SQL',
      '#description' => t('This SQL will be added to the query as a sort expression.'),
      '#default_value' => $this->options['raw_sql'],
    );

  } // options_form

  /**
   * Simple submit handler
   */
  function options_submit(&$form, &$form_state) {

    $this->options['raw_sql'] = $form_state['values']['options']['raw_sql'];

  } // options_submit

} // views_handler_sort_views_raw_sql