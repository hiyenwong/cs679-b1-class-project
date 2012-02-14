<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<title>Uncaught Exception</title>
		<style type="text/css" media="all">
			@import url("{$style_url}/admin.css");
		</style>
	</head>
	<body style="margin-left: 1em;">
		{include file="header.tpl"}

		<h2 style="border-bottom: 1px solid #999;">Internal Error</h2>
		<p>
			The system encountered an internal error and needed to exit. Please
			send an e-mail to the <a href="mailto:{$webmaster}">Webmaster</a>
			with the following information:
		</p>
		<div style="background: #fafafa; margin-left: 1em; margin-right: 2em; padding: 8px; font-size: small; border: 1px dashed #aaa;">
			Uncaught Exception in: {$exception->getFile()} on line: {$exception->getLine()}<br />
			<br />
			{$exception->getMessage()}
			<br />
			<pre>{$exception->getTraceAsString()}</pre>
		</div>

		{include file="footer.tpl"}
	</body>
</html>