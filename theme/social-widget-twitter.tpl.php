<?php
/**
 * @file
 * Template for twitter.
 *
 * https://twitter.com/intent/tweet?text=%node_body&url=%node_url
 */
?>
<script>
  function twitterShare(url, text, winWidth, winHeight) {
    var winTop = (screen.height / 2) - (winHeight / 2);
    var winLeft = (screen.width / 2) - (winWidth / 2);
    window.open('https://twitter.com/share?text=' + text + '&url=' + url,
      'twitter-tweet-dialog',
      'menubar=no,toolbar=no,resizable=yes,top=' + winTop + ',left=' + winLeft + ',width=' + winWidth + ',height=' + winHeight
    );
  }
</script>
<div class="<?php print $classes; ?>">
  <a href="javascript:twitterShare('<?php print $element['url']; ?>', '<?php print $element['text']; ?>', 600, 400)">
    <?php foreach ($element['icons'] as $icon): ?>
      <i class="<?php print $icon; ?>"></i>
    <?php endforeach; ?>
  </a>
  <script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>
</div>
