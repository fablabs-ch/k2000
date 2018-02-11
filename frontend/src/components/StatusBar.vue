<template>
  <div>{{data}}</div>
</template>

<script>

export default {
  data () {
    return {
      data: {}
    }
  },
  created () {
    const evtSource = new EventSource(`${this.$url.options.root}sse/status`)
    evtSource.onmessage = (e) => {
      this.data = JSON.parse(e.data)
    }
    evtSource.onerror = (e) => {
      console.log('EventSource failed.')
    }
  }
}
</script>

<style>

</style>
