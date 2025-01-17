(function($) {

/**
 * Behavior for the Konami Code module administration page.
 */
Backdrop.behaviors.konamicodeadmin = {
  attach: function(context, settings) {
    // Add the Demonstration link.
    $('#konamicode-admin-settings fieldset', context).once('konamicode-test', function() {
      // See which action we're dealing with.
      var action = $(this).data('konamicodeaction');

      // Construct the demonstation link.
      var demo = ' <a href="#" class="test-' + action + '">' + Backdrop.t('Demonstration') + '</a>';

      // Add it to the action summary.
      $('.fieldset-description', this).append(demo).children('.test-' + action).click(function() {
        Backdrop['konamicode_' + action]();
      });
    });

    // Update the Vertical Tab summaries when an Action is toggled.
    $('#edit-konamicode-actions input.form-checkbox', context).once('konamicodeclick').click(function() {
      // Call the Konami Code behavior.
      Backdrop.behaviors.konamicodeadmin.attach(context, settings);
    });

    // Construct the Vertical Tab summaries.
    $('#konamicode-admin-settings fieldset', context).backdropSetSummary(function (context) {
      // See which action we're getting the summary for.
      var action = $(context).data('konamicodeaction');
      // Check if the action is enabled.
      if ($('input[name="konamicode_actions[' + action + ']"]').attr('checked')) {
        // Just say it's enabled.
        return Backdrop.t('Enabled');
      }
      else {
        // Don't display a summary if the action is disabled.
        return Backdrop.t('');
      }
    });
  }
};

})(jQuery);
