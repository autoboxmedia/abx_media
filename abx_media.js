(function ($, Drupal, window, document) {

'use strict';

Drupal.behaviors.abxMedia = {
  attach: function (context) {
	  //media browser as page view clicks through to edit
      $('.media-item').click(function(){
	      window.location.pathname = 'file/' + $(this).attr('data-fid') + '';
      });
  }
  
};

}(jQuery, Drupal, this, this.document));
