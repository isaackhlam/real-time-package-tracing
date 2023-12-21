import merge from 'lodash/merge.js';

import * as healthcheck from './healthcheck.js';
import * as user from './user.js';
import * as parcel from './parcel.js';

const resolvers = merge({}, ...[healthcheck], ...[user], ...[parcel]);

export default resolvers;
