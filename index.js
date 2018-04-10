const path = require('path');
const argv = require('minimist')(process.argv.slice(2));
const fontFixer = require('./lib/font-fixer');

const debug = require('@ff0000-ad-tech/debug');
var log = debug('font-fixer');

log('CLI args:')
log(argv);

if (argv._.length) {
	fontFixer(path.resolve(argv._[0]));
}
