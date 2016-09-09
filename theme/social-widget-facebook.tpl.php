<?php
/**
 * @file
 * Template for facebook.
 *
 * https://www.facebook.com/sharer/sharer.php?u=%node_url
 */
?>
<script>
  function fbShare(url, winWidth, winHeight) {
    var winTop = (screen.height / 2) - (winHeight / 2);
    var winLeft = (screen.width / 2) - (winWidth / 2);
    window.open('https://www.facebook.com/sharer/sharer.php?u=' + url,
      'facebook-share-dialog',
      'width=' + winWidth + ',height=' + winWidth + ',top=' + winTop + ',left=' + winLeft
    );
    return false;
  }
</script>
<div class="<?php print $classes; ?>">
    <a href="javascript:fbShare('<?php print $element['url']; ?>', 520, 350)">
      <?php foreach ($element['icons'] as $icon): ?>
        <i class="<?php print $icon; ?>"></i>
      <?php endforeach; ?>
    </a>
</div>
