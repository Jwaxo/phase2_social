<?php
/**
 * @file
 * Template for social links.
 */
?>

<div class="social-share-links">
  <?php foreach ($networks as $network): ?>
    <?php if ($network === 'facebook'): ?>
      <span class="facebook">
        <div id="fb-root"></div>
        <script>
          (function(d, s, id){
            var js, fjs = d.getElementsByTagName(s)[0];
            if (d.getElementById(id)) {return;}
            js = d.createElement(s); js.id = id;
            js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.7";
            fjs.parentNode.insertBefore(js, fjs);
          }(document, 'script', 'facebook-jssdk'));
        </script>

        <div class="fb-share-button" data-href="<?php print $links[$network]['url']; ?>" data-layout="button" data-size="large" data-mobile-iframe="true">
          <a class="fb-xfbml-parse-ignore" target="_blank" href="<?php print $links[$network]['data']; ?>&amp;src=sdkpreparse">Facebook</a>
        </div>
      </span>
    <?php else: ?>
      <span class="social-link-<?php print $network; ?>"><?php print render($links[$network]); ?></span>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
