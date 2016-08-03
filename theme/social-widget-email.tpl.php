<?php
/**
 * @file
 * Template for email.
 *
 * mailto:?subject=%node_title&body=%node_body
 */
?>
<div class="<?php print $classes; ?>">
  <a href="mailto:?subject=<?php print urldecode($subject); ?>&body=<?php print urldecode($body); ?>">
    <?php foreach ($icons as $icon): ?>
      <i class="<?php print $icon; ?>"></i>
    <?php endforeach; ?>
  </a>
</div>
