{include file="header.tpl"}

<h2 style="border-bottom: 1px solid #999;">Error</h2>
<p style="font-size: medium;">{$error_message}</p>
{if $exception}
	<div style="background: #fafafa; margin-left: 1em; margin-right: 2em; padding: 8px; font-size: small; border: 1px dashed #aaa;">
		<pre>{$exception->getTraceAsString()}</pre>
	</div>
{/if}
<p style="font-size: small; padding-left: 1em;">
	<i>Time: {$smarty.now}</i><br />
	<i>Location: {$smarty.server.REQUEST_URI}</i><br />
	{if $smarty.server.HTTP_REFERER}
		<i>Referer: {$smarty.server.HTTP_REFERER}</i><br />
	{/if}
	{if $smarty.server.HTTP_USER_AGENT}
		<i>Agent: {$smarty.server.HTTP_USER_AGENT}</i><br />
	{/if}
</p>
<p>
	If you believe you have reached this page in error please contact the
	<a href="mailto:{$webmaster}">Webmaster</a>
	with the above information.
</p>

{include file="footer.tpl"}

