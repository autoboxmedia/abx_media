# Custom Media Features
## Enhancements for the Media suite

This adds a few tweaks to make Media on Drupal better.

### What it does
- Adds clickthrough functionality to a Media Browser page view — just make a display on the View
- Adds an “Add Media” menu link — recommend setting the above page View to admin/content/media to act as the menu parent
- Adds a file display formatter to allow a straight, actual URL path link to media — good for linking PDF docs

### Nice modules to have
- CKEditor Media Browser (hooks up the CKE file browser to the media popup)
- Media CKEditor (allows dropping media straight into CKE)

### Using Media CKEditor/CKEditor Media Browser
- Funnel file insert to CKE file linking, using the Media Browser
- Use Media CKEditor *only* for inserting video, which should really be its own thing
    - To this end, you can replace the standard icon at modules/media_ckeditor/js/plugins/media/icons with [media.png], included with this module