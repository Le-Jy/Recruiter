function getNumberFields(inputObject) {
    if (inputObject === null || typeof inputObject != 'object') {
        return [];
    }

    return Object.keys(inputObject).filter(key => typeof inputObject[key] === 'number');
}

function incrementCounters(inputObject) {
    if (typeof inputObject !== 'object' || inputObject === null) {
        return;
    }

    for (let key in inputObject) {
        if (inputObject.hasOwnProperty(key)) {
            if (/counter/i.test(key) && typeof inputObject[key] === 'number') {
                inputObject[key]++;
            }
            else if (typeof inputObject[key] === 'object') {
                incrementCounters(inputObject[key]);
            }
        }
    }
}

function deleteUppercaseProperties(inputObject) {
    if (typeof inputObject !== 'object' || inputObject === null) {
        return;
    }

    for (let key in inputObject) {
        if (inputObject.hasOwnProperty(key)) {
            if (/^[A-Z\s\d]+$/.test(key)) {
                delete inputObject[key];
            } else if (typeof inputObject[key] === 'object') {
                deleteUppercaseProperties(inputObject[key]);
            }
        }
    }
}

function fusion(...objs) {
    let result = {};

    objs.forEach(obj => {
        for (let key in obj) {
            if (obj.hasOwnProperty(key)) {
                if (result.hasOwnProperty(key)) {
                    if (obj[key] === undefined || result[key] === undefined || obj[key] === null || result[key] === null) {
                        result[key] = obj[key];
                    } else if (Array.isArray(obj[key]) && Array.isArray(result[key])) {
                        result[key] = result[key].concat(obj[key]);
                    } else if (typeof obj[key] === 'object' && typeof result[key] === 'object') {
                        result[key] = fusion(result[key], obj[key]);
                    } else if (typeof obj[key] === 'boolean' && typeof result[key] === 'boolean') {
                        result[key] = obj[key];
                    } else {
                        result[key] += obj[key];
                    }
                } else {
                    result[key] = obj[key];
                }
            }
        }
    });

    return result;
}

module.exports = {
    getNumberFields,
    incrementCounters,
    deleteUppercaseProperties,
    fusion
}