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
//    window.open('http://www.facebook.com/sharer.php?s=100' + title + '&p[summary]=' + descr + '&p[url]=' + url + '&p[images][0]=' + image, 'sharer', 'top=' + winTop + ',left=' + winLeft + ',toolbar=0,status=0,width=' + winWidth + ',height=' + winHeight);
  }
</script>
<div class="<?php print $classes; ?>">
    <a href="javascript:fbShare('<?php print $url; ?>', 520, 350)">
      <?php foreach ($icons as $icon): ?>
        <i class="<?php print $icon; ?>"></i>
      <?php endforeach; ?>
    </a>
</div>
