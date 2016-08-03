<?php
/**
 * @file
 * Primary widget template for social links.
 */
?>

<div class="social-share-links">
  <?php foreach ($shares as $name => $share): ?>
    <?php print $share ?>
  <?php endforeach; ?>
</div>
