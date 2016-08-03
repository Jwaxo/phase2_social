<?php
/**
 * @file
 * Template for linkedin.
 *
 * https://www.linkedin.com/shareArticle?mini=true&url=%node_url&title=%node_tit
 * le&summary=%node_body&source=%node_url
 */
?>
<script>
  function linkedinShare(url, title, summary, winWidth, winHeight) {
    var winTop = (screen.height / 2) - (winHeight / 2);
    var winLeft = (screen.width / 2) - (winWidth / 2);
    window.open('https://www.linkedin.com/shareArticle?mini=true&url=' + url + '&title=' + title + '&summary=' + summary + '&source=' + url,
      'linkedin-dialog',
      'menubar=no,toolbar=no,resizable=yes,top=' + winTop + ',left=' + winLeft + ',width=' + winWidth + ',height=' + winHeight
    );
  }
</script>
<div class="<?php print $classes; ?>">
  <a href="javascript:linkedinShare('<?php print $url; ?>', '<?php print $title; ?>', '<?php print $summary; ?>', 520, 350)">
    <?php foreach ($icons as $icon): ?>
      <i class="<?php print $icon; ?>"></i>
    <?php endforeach; ?>
  </a>
</div>
