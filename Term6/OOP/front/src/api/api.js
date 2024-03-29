export async function client(endpoint, { body, ...customConfig } = {}) {
  const headers = { 'Content-Type': 'application/json'}

  const config = {
    ...customConfig,
    headers: {
      ...headers,
      ...customConfig.headers,
    },
    credentials: 'include',
  }

  if (body) {
    config.body = JSON.stringify(body)
  }

  let data
  try {
    const response = await window.fetch(endpoint, config)
    data = await response.json()
    if (response.ok) {
      // Return a result object similar to Axios
      return {
        status: response.status,
        data,
        headers: response.headers,
        url: response.url,
      }
    }
    throw new Error(response.statusText)
  } catch (err) {
    return Promise.reject(err.message ? err.message : data)
  }
}

const prefix = ''

client.get = function (endpoint, customConfig = {}) {
  return client(prefix + endpoint, { ...customConfig, method: 'GET' })
}

client.post = function (endpoint, body, customConfig = {}) {
  return client(prefix + endpoint, { ...customConfig, body, method: 'POST' })
}

client.put = function (endpoint, body, customConfig = {}) {
  return client(prefix + endpoint, { ...customConfig, body, method: 'PUT' })
}

client.delete = function (endpoint, body, customConfig = {}) {
  return client(prefix + endpoint, { ...customConfig, body, method: 'DELETE' })
}
