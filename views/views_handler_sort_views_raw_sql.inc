<?php

/**
 * A handler to provide a field that is completely custom SQL by the administrator.
 *
 * @ingroup views_field_handlers
 */
class views_handler_sort_views_raw_sql extends views_handler_sort {

  function query() {

    $raw_sql = $this->options['raw_sql'];
    // Get replacement tokens.
    $tokens = views_raw_sql_get_query_tokens($this->view);
    // And replace.
    $raw_sql = str_replace(array_keys($tokens), $tokens, $raw_sql);

    $this->query->add_orderby(NULL, $raw_sql, $this->options['order'], 'raw_sql_order');

  } // query

  function option_definition() {

    $options = parent::option_definition();

    $options['raw_sql'] = array('default' => '');

    return $options;

  } // option_definition

  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form['raw_sql'] = array(
      '#type' => 'textarea',
      '#title' => 'SQL',
      '#description' => t('This SQL will be added to the query as a sort expression.')
        . ' ' . views_raw_sql_tokens_help(),
      '#default_value' => $this->options['raw_sql'],
      '#required' => TRUE,
    );

    if (!user_access('edit views raw sql')) {
      $form['raw_sql']['#disabled'] = TRUE;
      $form['raw_sql']['#description'] = t('You lack %permission permission to edit this sort.', array('%permission' => 'edit views raw sql'));
    } // if

  } // options_form

  /**
   * Simple submit handler
   */
  function options_submit(&$form, &$form_state) {

    $this->options['raw_sql'] = $form_state['values']['options']['raw_sql'];

  } // options_submit

} // views_handler_sort_views_raw_sql
